/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-ais <rben-ais@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:35:40 by redadgh           #+#    #+#             */
/*   Updated: 2025/08/20 22:26:02 by rben-ais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	exec_external(t_env **env, t_cmd *cmd)
{
	pid_t	pid;
	char	**envp;
	char	*cmd_path;

	cmd_path = find_command_path(cmd->args[0], *env);
	if (!cmd_path)
	{
        if (ft_strchr(cmd->args[0], '/') && access(cmd->args[0], F_OK) == 0)
            printf("%s: Permission denied\n", cmd->args[0]);
        else
            printf("%s: command not found\n", cmd->args[0]);
        return ;
	}
	envp = env_to_array(*env);
	pid = fork();
	if (pid == 0)
	{
		if (setup_redirection(cmd) == -1)
			return;
		execve(cmd_path, cmd->args, envp);
		perror("execve faild");
		exit(127);
	}
	else if (pid > 0)
		waitpid (pid, NULL, 0);
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

void	exec_builtin(t_env **env, t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		ft_echo(cmd->args);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		ft_cd(cmd->args, env);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd->args[0], "env"))
		ft_env(env);
	else if (!ft_strcmp(cmd->args[0], "export"))
		ft_export(cmd->args, env);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		ft_unset(cmd->args, env);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		ft_exit(cmd->args);
}

void	execution(t_env **env, t_cmd *cmd)
{
	t_cmd   *tmp;

	if (!cmd || !env || !*env)
		return;
	tmp = cmd;
	if (tmp->next)
	{
		execute_pipeline(env, tmp);
		return;
	}
	if (!tmp->args || !tmp->args[0] || !tmp->args[0][0])
		return;
	if (is_builtin(tmp->args[0]))
		exec_builtin(env, tmp);
	else
		exec_external(env, tmp);
}

