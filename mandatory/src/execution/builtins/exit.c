/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:14:16 by rben-ais          #+#    #+#             */
/*   Updated: 2025/08/24 21:07:09 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_number(char *str)
{
    int	i;

    if (!str || !*str)
        return (0);
    i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    if (!str[i])  // Only sign character
        return (0);
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

void	ft_exit(t_shell *shell, char **args)
{
	int		arg_count;

	arg_count = 0;
	while(args[arg_count])
		arg_count++;
	if (arg_count == 1)
	{
		shell->exit_status = EXIT_SUCCESS;
		exit(shell->exit_status);
	}
	else if (!is_number(args[1]))
	{
		printf("shellnobyl: exit: %s: numeric argument required\n", args[1]);
		shell->exit_status = EXIT_SYNTAX;
		exit(shell->exit_status = EXIT_SYNTAX);
	}
	else if (arg_count > 2)
	{
		printf("shellnobyl: exit: too many arguments\n");
		shell->exit_status = EXIT_AMBIGUOUS_REDIR;
		exit(shell->exit_status);
	}
	else
	{
		shell->exit_status = ft_atoi(args[1]) % EXIT_STATUS_MASK;
		exit(shell->exit_status);
	}
}
