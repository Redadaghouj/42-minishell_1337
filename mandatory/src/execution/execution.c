/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-ais <rben-ais@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:35:40 by redadgh           #+#    #+#             */
/*   Updated: 2025/08/02 16:21:12 by rben-ais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_external(t_env **env, t_cmd *cmd)
{
	(void) env;
	(void) cmd;
	return;
}

static int	is_builtin(char *cmd)
{
	if (!cmd)
		return(0);
	if (!ft_strcmp(cmd, "echo")
	||	!ft_strcmp(cmd, "cd")
	||	!ft_strcmp(cmd, "pwd")
	||	!ft_strcmp(cmd, "export")
	||	!ft_strcmp(cmd, "unset")
	||	!ft_strcmp(cmd, "env")
	||	!ft_strcmp(cmd, "exit"))
		return(1);
	else
		return (0);
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
