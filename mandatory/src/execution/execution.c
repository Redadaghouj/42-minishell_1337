/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-ais <rben-ais@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:35:40 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/30 15:39:36 by rben-ais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
static int	is_builtin(const char *cmd)
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
		if (is_builtin(tmp->args))
			exec_builtin(env, tmp);
		else
			exec_external(env, tmp);
		tmp = tmp->next;
	}
}
