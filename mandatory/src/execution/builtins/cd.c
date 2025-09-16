/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 23:03:45 by rben-ais          #+#    #+#             */
/*   Updated: 2025/09/16 09:57:03 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	ft_cd(t_shell *shell, char **args)
{
	char	*home;

	shell->exit_status = EXIT_SUCCESS;
	if (!args[1])
	{
		home = get_env_value(ft_strdup("HOME"), shell->env);
		if (!home || chdir(home))
		{
			shell->exit_status = EXIT_FAILURE;
			if (!home)
				ft_putstr_fd("shellnobyl: cd: HOME not set\n", STDERR_FILENO);
			else
				perror("shellnobyl: cd");
		}
	}
	else if (args[2])
	{
		shell->exit_status = EXIT_FAILURE;
		ft_putstr_fd("shellnobyl: cd: too many arguments\n", STDERR_FILENO);
	}
	else if (chdir(args[1]))
	{
		shell->exit_status = EXIT_FAILURE;
		builtin_err("cd: ", args[1], ": No such file or directory\n");
	}
}
