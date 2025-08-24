/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:09:56 by rben-ais          #+#    #+#             */
/*   Updated: 2025/08/24 20:42:37 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int		is_n_flag(char *str)
{
	int	i;
	
	if (str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_shell *shell, char **args)
{
	int	i;
	int	new_linef;

	i = 1;
	new_linef = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		new_linef = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (new_linef)
		ft_putstr_fd("\n", 1);
	shell->exit_status = EXIT_SUCCESS;
}
