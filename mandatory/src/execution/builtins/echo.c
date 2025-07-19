/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-ais <rben-ais@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:09:56 by rben-ais          #+#    #+#             */
/*   Updated: 2025/07/19 22:42:37 by rben-ais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/execution.h"

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

void	ft_echo(char **arv)
{
	int	new_linef;
	int	i;

	i = 1;
	new_linef = 1;
	while (arv[i] && is_n_flag(arv[i]))
	{
		new_linef = 0;
		i++;
	}
	while (arv[i])
	{
		ft_putstr_fd(arv[i], 1);
		if (arv[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (new_linef)
		ft_putstr_fd("\n", 1);
}
