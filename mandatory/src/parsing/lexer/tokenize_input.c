/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-ais <rben-ais@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 10:41:06 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/08/21 12:36:10 by rben-ais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_operator(char c)
{
	return (is_pipe(c) || is_redir_in(c) || is_redir_out(c));
}

void	create_token(char *input, t_token **list, int start, int end)
{
	t_token	*node;
	char	*value;

	if (end <= start)
		return ;
	value = ft_substr(input, start, end - start);
	if (!value)
	{
		ft_lstclear_token(list);
		exit(EXIT_FAILURE);
	}
	node = ft_lstnew_token(value);
	if (is_pipe(value[0]))
		node->type = TOKEN_PIPE;
	else if (is_append_out(value))
		node->type = TOKEN_APPEND_OUT;
	else if (is_heredoc(value))
		node->type = TOKEN_HEREDOC;
	else if (is_redir_out(value[0]))
		node->type = TOKEN_REDIR_OUT;
	else if (is_redir_in(value[0]))
		node->type = TOKEN_REDIR_IN;
	else
		node->type = TOKEN_WORD;
	ft_lstadd_back_token(list, node);
}

void	split_by_operator(char *input, t_token **list, int *start, int *end)
{
	create_token(input, list, *start, *end);
	if (is_append_out(input + *end) || is_heredoc(input + *end))
	{
		create_token(input, list, *end, *end + 2);
		(*end)++;
	}
	else
		create_token(input, list, *end, *end + 1);
	*start = *end + 1;
}

void	split_by_space(char *input, t_token **list, int *start, int *end)
{
	create_token(input, list, *start, *end);
	while (input[*end] == ' ')
		(*end)++;
	*start = *end;
	(*end)--;
}

void	lexer(char *input, t_token **list)
{
	int		i;
	int		start;
	char	quote;

	i = 0;
	start = 0;
	quote = 0;
	while (input[i])
	{
		if ((input[i] == SQUOTE || input[i] == DQUOTE) && !quote)
			quote = input[i];
		else if (quote == input[i])
			quote = 0;
		else if (is_operator(input[i]) && !quote)
			split_by_operator(input, list, &start, &i);
		else if (input[i] == ' ' && !quote)
			split_by_space(input, list, &start, &i);
		i++;
	}
	create_token(input, list, start, i);
}
