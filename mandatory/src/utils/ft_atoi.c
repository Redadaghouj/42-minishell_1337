/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-ais <rben-ais@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 21:39:56 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/08/01 19:48:05 by rben-ais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	skip_isspace(const char *nptr)
{
	int	i;

	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	return (i);
}

int	check_sign(const char *nptr, int i, int *sign)
{
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	res;
	int	prev_res;	

	i = skip_isspace(nptr);
	sign = 1;
	res = 0;
	i = check_sign(nptr, i, &sign);
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		prev_res = res;
		res = res * 10 + (nptr[i] - '0') * sign;
		if (sign == 1 && prev_res > res)
			return (-1);
		else if (sign == -1 && prev_res < res)
			return (0);
		i++;
	}
	return (res);
}