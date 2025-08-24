/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:35:40 by redadgh           #+#    #+#             */
/*   Updated: 2025/08/24 21:11:20 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdlib.h>

static char **env_to_array(t_env *env)
{
	char	**envp;
	char	*temp;
	t_env	*tmp;
	int		count;
	int		i;

	count = count_and_allocate(env, &envp);
	if (count == -1)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp && i < count)
	{
		if (tmp->value)
		{
			temp = rb_strjoin(tmp->key, "=");
			envp[i] = rb_strjoin(temp, tmp->value);
			free(temp);
			i++;
		}
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	exec_external(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	char	**envp;
	char	*cmd_path;
	int		status;

	cmd_path = find_command_path(cmd->args[0], shell->env);
	if (!cmd_path)
	{
        if (ft_strchr(cmd->args[0], '/') && access(cmd->args[0], F_OK) == 0)
		{
			shell->exit_status = EXIT_PERMISSION;
            printf("shellnobyl: %s: Permission denied\n", cmd->args[0]);
		}
        else
		{
			shell->exit_status = EXIT_CMD_NOT_FOUND;
            printf("shellnobyl: %s: command not found\n", cmd->args[0]);
		}
        return ;
	}
	envp = env_to_array(shell->env);
	pid = fork();
	if (pid == 0)
	{
		if (setup_redirection(cmd) == -1)
			exit(EXIT_AMBIGUOUS_REDIR);
		execve(cmd_path, cmd->args, envp);
		perror("execve failed");
		exit(EXIT_CMD_NOT_FOUND);
	}
	else if (pid > 0)
	{
		waitpid (pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
	}
	free (cmd_path);
	free_array(envp);
}

void	exec_external_child(t_env **env, t_cmd *cmd)
{
    char	**envp;
    char	*cmd_path;

    cmd_path = find_command_path(cmd->args[0], *env);
    if (!cmd_path)
    {
        if (ft_strchr(cmd->args[0], '/') && access(cmd->args[0], F_OK) == 0)
            ft_putstr_fd("Permission denied\n", STDERR_FILENO);
        else
		{
            ft_putstr_fd(cmd->args[0], STDERR_FILENO);
            ft_putstr_fd(": command not found\n", STDERR_FILENO);
		}
        exit(127);
    }
    envp = env_to_array(*env);
    execve(cmd_path, cmd->args, envp);
    perror("execve");
    exit(127);
}

bool	setup_with_backup(t_cmd *cmd, int *save_stdout, int *save_stdin)
{
	*save_stdout = dup(STDOUT_FILENO);
	*save_stdin = dup(STDIN_FILENO);
	if (setup_redirection(cmd) == -1)
	{
		close(*save_stdout);
		close(*save_stdin);
		return (false);
	}
	return (true);
}

void	restore_stdio(int save_stdout, int save_stdin)
{
	dup2(save_stdout, STDOUT_FILENO);
	dup2(save_stdin, STDIN_FILENO);
	close(save_stdin);
	close(save_stdout);
}

void	exec_builtin(t_shell *shell, char **args)
{
	int		save_stdout;
	int		save_stdin;

	if (!setup_with_backup(shell->cmd, &save_stdout, &save_stdin))
		return ;
	if (!ft_strcmp(args[0], "echo"))
		ft_echo(shell, args);
	else if (!ft_strcmp(args[0], "cd"))
		ft_cd(shell, args);
	else if (!ft_strcmp(args[0], "pwd"))
		ft_pwd(shell);
	else if (!ft_strcmp(args[0], "env"))
		ft_env(shell);
	else if (!ft_strcmp(args[0], "export"))
		ft_export(shell, args);
	else if (!ft_strcmp(args[0], "unset"))
		ft_unset(shell, args);
	else if (!ft_strcmp(args[0], "exit"))
		ft_exit(shell, args);
	restore_stdio(save_stdout, save_stdin);
}

void	execution(t_shell *shell)
{
	t_cmd   *tmp;
	int		prev_fd;

	if (!shell || !shell->cmd || !shell->env)
		return;
	tmp = shell->cmd;
	prev_fd = -1;
	if (tmp->next)
	{
		execute_pipeline(shell, prev_fd);
		return;
	}
	if (!tmp->args || !tmp->args[0] || !tmp->args[0][0])
		return;
	if (is_builtin(tmp->args[0]))
		exec_builtin(shell, tmp->args);
	else
		exec_external(shell, tmp);
}

