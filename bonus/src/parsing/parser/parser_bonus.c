/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:22:31 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/08/26 23:23:22 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_bonus.h"

void	count_cmd_and_redir(t_token *list, int *redir_nbr, int *i)
{
	*i = 0;
	*redir_nbr = 0;
	while (list && list->type != TOKEN_PIPE)
	{
		if (list->type != TOKEN_WORD)
		{
			(*redir_nbr)++;
			list = list->next;
		}
		else
			(*i)++;
		list = list->next;
	}
}

char	**fill_args(t_token *list, int cmd_nbr)
{
	char	**args;
	int		i;

	i = 0;
	args = (char **)malloc(sizeof(char *) * (cmd_nbr + 1));
	if (!args)
		return (NULL);
	while (i < cmd_nbr)
	{
		if (list->type != TOKEN_PIPE && list->type != TOKEN_WORD)
			list = list->next->next;
		else
		{
			args[i] = ft_strdup(list->value);
			list = list->next;
			i++;
		}
	}
	args[i] = NULL;
	return (args);
}

void	fill_redir(t_token *list, t_cmd **cmd, int redir_nbr)
{
	t_redir			*redir;
	t_redir			*node;
	unsigned int	type;
	char			*value;

	redir = NULL;
	while (list && redir_nbr > 0)
	{
		type = list->type;
		value = ft_strdup(list->next->value);
		node = ft_lstnew_redir(type, value);
		ft_lstadd_back_redir(&redir, node);
		list = list->next->next;
		redir_nbr--;
	}
	(*cmd)->redir = redir;
}

t_token	*fill_redir_and_skip(t_token *list, t_cmd **node, int redir_nbr, int j)
{
	if (redir_nbr > 0)
	{
		fill_redir(list, node, redir_nbr);
		while (redir_nbr-- > 0)
			list = list->next->next;
		while (list && j-- > 0)
			list = list->next;
	}
	return (list);
}

void	parser(t_token *list, t_shell *shell)
{
	int		i;
	int		j;
	int		redir_nbr;
	t_cmd	*node;

	if (!check_syntax(list))
	{
		while (list)
		{
			if (list->type != TOKEN_PIPE)
			{
				count_cmd_and_redir(list, &redir_nbr, &i);
				j = i - 1;
				node = ft_lstnew_cmd(fill_args(list, i));
				while (i-- > 0 && list->type == TOKEN_WORD)
					list = list->next;
				list = fill_redir_and_skip(list, &node, redir_nbr, j);
				ft_lstadd_back_cmd(&shell->cmd, node);
			}
			else
				list = list->next;
		}
	}
	else
		shell->exit_status = EXIT_SYNTAX;
}
