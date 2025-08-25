/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:28:46 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/08/25 23:11:50 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**help_external(t_shell *shell,
	t_cmd *cmd, char *cmd_path)
{
	char	**envp;
	int		status;
	pid_t	pid;

	envp = env_to_array(shell->env);
	status = 0;
	pid = fork();
	if (pid == 0)
	{
		reset_and_catch_sig(shell, status, true);
		if (setup_redirection(cmd) == -1)
			exit(EXIT_AMBIGUOUS_REDIR);
		execve(cmd_path, cmd->args, envp);
		perror("execve failed");
		exit(EXIT_CMD_NOT_FOUND);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		reset_and_catch_sig(shell, status, false);
	}
	return (envp);
}

void	exec_external(t_shell *shell, t_cmd *cmd)
{
	char	**envp;
	char	*cmd_path;

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
			if (ft_strchr(cmd->args[0], '/') || !cmd_path)
				printf("shellnobyl: %s: No such file or directory\n",
					cmd->args[0]);
			else
				printf("shellnobyl: %s: command not found...\n", cmd->args[0]);
			shell->exit_status = EXIT_CMD_NOT_FOUND;
		}
		return ;
	}
	envp = help_external(shell, cmd, cmd_path);
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
			ft_putstr_fd("shellnobyl: Permission denied\n", STDERR_FILENO);
		else
		{
			ft_putstr_fd("shellnobyl: ", STDERR_FILENO);
			ft_putstr_fd(cmd->args[0], STDERR_FILENO);
			ft_putstr_fd(": command not found...\n", STDERR_FILENO);
		}
		exit(127);
	}
	envp = env_to_array(*env);
	execve(cmd_path, cmd->args, envp);
	perror("execve");
	exit(127);
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
	dup2(save_stdout, STDOUT_FILENO);
	dup2(save_stdin, STDIN_FILENO);
	close(save_stdin);
	close(save_stdout);
}

void	execution(t_shell *shell)
{
	t_cmd	*tmp;
	int		prev_fd;

	if (!shell || !shell->cmd)
		return ;
	tmp = shell->cmd;
	prev_fd = -1;
	if (tmp->next)
	{
		execute_pipeline(shell, prev_fd, -1);
		return ;
	}
	if (!tmp->args || !tmp->args[0] || !tmp->args[0][0])
		return ;
	if (is_builtin(tmp->args[0]))
		exec_builtin(shell, tmp->args);
	else
		exec_external(shell, tmp);
}
