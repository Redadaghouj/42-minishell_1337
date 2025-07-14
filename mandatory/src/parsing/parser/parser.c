/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:22:31 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/07/14 14:24:19 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void print_args(char **args)
{
    int i = 0;
    while (args && args[i])
    {
        printf("args[%d]: %s\n", i, args[i]);
        i++;
    }
    printf("args[%d]: NULL\n", i);
}

char  *return_type(unsigned int type)
{
	if (type == TOKEN_HEREDOC)
		return("<<");
	else if (type == TOKEN_APPEND_OUT)
		return(">>");
	else if (type == TOKEN_REDIR_IN)
		return("<");
	else if (type == TOKEN_REDIR_OUT)
		return(">");
	else
		return("NON");
}

void	print_redirs(t_redir *redir)
{
	int i = 0;
	while (redir)
	{
		printf("  redir[%d]: file='%s', type='%s'\n", i, redir->file_delim, return_type(redir->type));
		redir = redir->next;
		i++;
	}
	if (i == 0)
		printf("  no redirs\n");
}

void	print_cmd_list(t_cmd *cmd)
{
	int cmd_i = 0;
	while (cmd)
	{
		printf("cmd[%d]:\n", cmd_i);

		// Print args
		if (cmd->args)
		{
			for (int i = 0; cmd->args[i]; i++)
				printf("  args[%d]: %s\n", i, cmd->args[i]);
		}
		else
			printf("  no args\n");

		// Print redirs
		print_redirs(cmd->redir);

		cmd = cmd->next;
		cmd_i++;
	}
}

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

void	parser(t_token *list, t_cmd **cmd)
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
				ft_lstadd_back_cmd(cmd, node);
			}
			else
				list = list->next;
		}
	}
}
