/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-ais <rben-ais@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:59:34 by rben-ais          #+#    #+#             */
/*   Updated: 2025/07/21 14:21:29 by rben-ais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/execution.h"

void	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
	}
	else
		perror("Error :pwd not working");
}
