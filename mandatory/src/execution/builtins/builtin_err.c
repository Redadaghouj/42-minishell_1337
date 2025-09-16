/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:53:34 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/09/16 09:56:42 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	builtin_err(char *prefix, char *str, char *postfix)
{
	ft_putstr_fd("shellnobyl: ", STDERR_FILENO);
	ft_putstr_fd(prefix, STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(postfix, STDERR_FILENO);
}
