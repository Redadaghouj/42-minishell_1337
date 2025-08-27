/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lists_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:22:31 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/08/26 23:23:29 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_bonus.h"

t_cmd	*ft_lstnew_cmd(char **args)
{
	t_cmd	*node;

	node = (t_cmd *) malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->args = args;
	node->redir = NULL;
	node->next = NULL;
	return (node);
}

t_cmd	*ft_lstlast_cmd(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	free_redir(t_redir *lst)
{
	t_redir	*ptr;

	while (lst)
	{
		ptr = lst->next;
		free(lst->file_delim);
		free(lst);
		lst = ptr;
	}
}

void	ft_lstclear_cmd(t_cmd **lst)
{
	t_cmd	*ptr;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		ptr = (*lst)->next;
		free_buffer((*lst)->args);
		free_redir((*lst)->redir);
		free(*lst);
		*lst = ptr;
	}
}

void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *node)
{
	t_cmd	*last;

	if (!lst || !node)
		return ;
	if (*lst == NULL)
		*lst = node;
	else
	{
		last = ft_lstlast_cmd(*lst);
		last->next = node;
	}
}
