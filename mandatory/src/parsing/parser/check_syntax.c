/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-ais <rben-ais@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 20:23:48 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/08/21 12:36:10 by rben-ais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	unclosed_quotes(char *value)
{
	char	quote;
	int		i;

	quote = 0;
	i = -1;
	while (value[++i])
	{
		if ((value[i] == SQUOTE || value[i] == DQUOTE) && !quote)
		{
			quote = value[i];
			continue ;
		}
		if (value[i] == quote)
			quote = 0;
	}
	if (quote != 0)
	{
		printf(ERR_UNCLOSED_QUOTES "`%c'\n", quote);
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
			printf(ERR_EMPTY_PIPE_UNEXPECTED_TOKEN);
			return (EXIT_FAILURE);
		}
		else if (!next)
		{
			printf(ERR_EMPTY_PIPE_UNEXPECTED_EOF);
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
			printf(ERR_INVALID_REDIR_UNEXPECTED_NEWLINE);
			return (EXIT_FAILURE);
		}
		else if (next->type != TOKEN_WORD)
		{
			printf(ERR_INVALID_REDIR_UNEXPECTED_TOKEN "`%s'\n", next->value);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	redir_fd(bool toggle, int *fd)
{
	if (toggle)
	{
		*fd = dup(STDOUT_FILENO);
		if (*fd == -1)
			return (EXIT_FAILURE);
		if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
		{
			close(*fd);
			return (EXIT_FAILURE);
		}
	}
	else
	{
		if (dup2(*fd, STDOUT_FILENO) == -1)
		{
			close(*fd);
			return (EXIT_FAILURE);
		}
		close(*fd);
	}
	return (EXIT_SUCCESS);
}

int	check_syntax(t_token *list)
{
	t_token	*prev_token;
	int		fd;

	prev_token = list;
	if (redir_fd(true, &fd))
		return (EXIT_FAILURE);
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
	if (redir_fd(false, &fd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
