/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:59:20 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/06/03 15:07:55 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_append_out(char *input)
{
	return (input[0] == '>' && input[1] == '>');
}

int	is_heredoc(char *input)
{
	return (input[0] == '<' && input[1] == '<');
}

int	is_redir_out(char c)
{
	return (c == '>');
}

int	is_redir_in(char c)
{
	return (c == '<');
}

int	is_pipe(char c)
{
	return (c == '|');
}
