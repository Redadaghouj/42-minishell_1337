/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:59:20 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/07/17 19:11:41 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
