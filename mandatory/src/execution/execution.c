/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-ais <rben-ais@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:35:40 by redadgh           #+#    #+#             */
/*   Updated: 2025/08/04 05:39:28 by rben-ais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

void	exec_external(t_env **env, t_cmd *cmd)
{
	pid_t	pid;
	char	**envp;
	char	*cmd_path;

	cmd_path = find_command_path(cmd->args[0], *env);
	if (!cmd_path)
	{
		printf("%s: command not found\n", cmd->args[0]);
		return;
	}
	envp = env_to_array(*env);
	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, cmd->args, envp);
		perror("execve faild");
		exit(127);
	}
	else if (pid > 0)
		waitpid (pid, NULL, 0);
	free (cmd_path);
	free_array(envp);
}

static void	exec_builtin(t_env **env, t_cmd *cmd)
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
	while (tmp)
	{
		if (!tmp->args || !tmp->args[0] || !tmp->args[0][0])
		{
			tmp = tmp->next;
			continue;
		}
		if (is_builtin(tmp->args[0]))
			exec_builtin(env, tmp);
		else
			exec_external(env, tmp);
		tmp = tmp->next;
	}
}
