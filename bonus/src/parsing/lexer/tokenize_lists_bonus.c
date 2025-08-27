/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_lists_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 10:41:06 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/08/26 23:22:44 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_bonus.h"

t_token	*ft_lstnew_token(char *value)
{
	t_token	*node;

	node = (t_token *) malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->value = value;
	node->next = NULL;
	return (node);
}

t_token	*ft_lstlast_token(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstclear_token(t_token **lst)
{
	t_token	*ptr;
	t_token	*curr;

	if (!lst)
		return ;
	ptr = *lst;
	while (ptr != NULL)
	{
		curr = ptr;
		ptr = ptr->next;
		free(curr->value);
		free(curr);
	}
	*lst = NULL;
}

void	ft_lstadd_back_token(t_token **lst, t_token *node)
{
	t_token	*last;

	if (!lst || !node)
		return ;
	if (*lst == NULL)
		*lst = node;
	else
	{
		last = ft_lstlast_token(*lst);
		last->next = node;
	}
}
