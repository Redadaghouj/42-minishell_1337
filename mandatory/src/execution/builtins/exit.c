/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-ais <rben-ais@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:14:16 by rben-ais          #+#    #+#             */
/*   Updated: 2025/08/01 15:47:23 by rben-ais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/execution.h"

void	ft_exit(char **args)
{
	int	exit_code;
	int	arg_count;

	printf("exit\n");
	arg_count = 0;
	while(args[arg_count])
		arg_count++;
	if (arg_count == 1)
		exit(0);
	if(!is_number(args[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit(2);
	}
	if(arg_count > 2)
	{
		printf("minishell: exit: too many arguments\n");
		return;
	}
	exit_code = ft_atoi(args[1]);
	exit(exit_code % 256);
}