/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:36:50 by rben-ais          #+#    #+#             */
/*   Updated: 2025/09/16 10:03:02 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_bonus.h"

void	ft_env(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (tmp->value)
		{
			ft_putstr_fd(tmp->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\n", 1);
		}
		tmp = tmp->next;
	}
	shell->exit_status = EXIT_SUCCESS;
}
