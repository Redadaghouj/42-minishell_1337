/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:22:31 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/07/14 13:33:40 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_redir	*ft_lstnew_redir(unsigned int type, char *file_delim)
{
	t_redir	*node;

	node = (t_redir *) malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	node->type = type;
	node->file_delim = file_delim;
	node->heredoc_fd = 0;
	node->should_expand = true;
	node->next = NULL;
	return (node);
}

t_redir	*ft_lstlast_redir(t_redir *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_redir(t_redir **lst, t_redir *node)
{
	t_redir	*last;

	if (!lst || !node)
		return ;
	if (*lst == NULL)
		*lst = node;
	else
	{
		last = ft_lstlast_redir(*lst);
		last->next = node;
	}
}
