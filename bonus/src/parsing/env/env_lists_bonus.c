/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lists_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:27:25 by redadgh           #+#    #+#             */
/*   Updated: 2025/08/26 23:20:32 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_bonus.h"

t_env	*ft_lstnew_env(char *value, char *key)
{
	t_env	*node;

	node = (t_env *) malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->value = value;
	node->key = key;
	node->next = NULL;
	return (node);
}

t_env	*ft_lstlast_env(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstclear_env(t_env **lst)
{
	t_env	*ptr;
	t_env	*curr;

	if (!lst)
		return ;
	ptr = *lst;
	while (ptr != NULL)
	{
		curr = ptr;
		ptr = ptr->next;
		free(curr->value);
		free(curr->key);
		free(curr);
	}
	*lst = NULL;
}

void	ft_lstadd_back_env(t_env **lst, t_env *node)
{
	t_env	*last;

	if (!lst || !node)
		return ;
	if (*lst == NULL)
		*lst = node;
	else
	{
		last = ft_lstlast_env(*lst);
		last->next = node;
	}
}
