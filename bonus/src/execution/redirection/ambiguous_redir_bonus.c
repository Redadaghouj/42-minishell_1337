/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_redir_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:39:17 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/08/26 23:20:01 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_bonus.h"

bool	is_ambiguous_filename(char *filename)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(filename) - 1;
	if (filename[0] == '\0')
	{
		ft_putstr_fd(ERR_AMBIGUOUS_REDIRECT, STDERR_FILENO);
		return (true);
	}
	while (filename[i] == ' ')
		i++;
	while (filename[i])
	{
		if (filename[i] == ' ' && i < len && filename[i + 1] != ' ')
		{
			ft_putstr_fd(ERR_AMBIGUOUS_REDIRECT, STDERR_FILENO);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	is_redir_ambiguous(t_redir *redir)
{
	if (redir->type != TOKEN_HEREDOC && redir->should_expand)
	{
		if (is_ambiguous_filename(redir->file_delim))
			return (true);
	}
	return (false);
}
