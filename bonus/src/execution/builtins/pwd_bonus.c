/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:59:34 by rben-ais          #+#    #+#             */
/*   Updated: 2025/08/26 23:19:24 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_bonus.h"

void	ft_pwd(t_shell *shell)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
		shell->exit_status = EXIT_SUCCESS;
	}
	else
	{
		perror("Error :pwd not working");
		shell->exit_status = EXIT_SUCCESS;
	}
}
