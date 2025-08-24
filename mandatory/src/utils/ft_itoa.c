/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 02:53:05 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/08/24 02:53:08 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_digits(int n, int *sign)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
		*sign = 1;
	}
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	int		i;

	if (n == 0)
		return (ft_strdup("0"));
	else if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	sign = 0;
	i = count_digits(n, &sign);
	str = (char *) malloc(i * sizeof(char) + 1);
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (sign)
	{
		str[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		str[i--] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
