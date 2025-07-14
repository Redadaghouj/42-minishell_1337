/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:23:48 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/07/09 01:22:08 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	unclosed_quotes(char *value)
{
	char	quote;
	int		i;

	quote = 0;
	i = -1;
	while (value[++i])
	{
		if ((value[i] == '\'' || value[i] == '"') && !quote)
		{
			quote = value[i];
			continue ;
		}
		if (value[i] == quote)
			quote = 0;
	}
	if (quote != 0)
	{
		printf("Shellnobyl: unexpected EOF while looking for matching ");
		printf("`%c'\n", quote);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	empty_pipe(t_token *prev, unsigned int type, t_token *next)
{
	if (type == TOKEN_PIPE)
	{
		if (prev->type != TOKEN_WORD)
		{
			printf("shellnobyl: syntax error near unexpected token `|'\n");
			return (EXIT_FAILURE);
		}
		else if (!next)
		{
			printf("shellnobyl: syntax error: unexpected end of file\n");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	invalid_redir(unsigned int type, t_token *next)
{
	if (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_APPEND_OUT || type == TOKEN_HEREDOC)
	{
		if (!next)
		{
			printf(SYNTAX_MSG);
			return (EXIT_FAILURE);
		}
		else if (next->type != TOKEN_WORD)
		{
			printf("shellnobyl: syntax error near unexpected token ");
			printf("`%s'\n", next->value);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	check_syntax(t_token *list)
{
	t_token	*prev_token;

	prev_token = list;
	while (list)
	{
		if (unclosed_quotes(list->value))
			return (EXIT_FAILURE);
		else if (empty_pipe(prev_token, list->type, list->next))
			return (EXIT_FAILURE);
		else if (invalid_redir(list->type, list->next))
			return (EXIT_FAILURE);
		prev_token = list;
		list = list->next;
	}
	return (EXIT_SUCCESS);
}
