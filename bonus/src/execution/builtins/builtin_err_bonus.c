/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_err_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:53:34 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/09/16 10:02:38 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_bonus.h"

void	builtin_err(char *prefix, char *str, char *postfix)
{
	ft_putstr_fd("shellnobyl: ", STDERR_FILENO);
	ft_putstr_fd(prefix, STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(postfix, STDERR_FILENO);
}
