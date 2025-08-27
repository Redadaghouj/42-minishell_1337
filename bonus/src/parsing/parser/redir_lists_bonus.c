/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lists_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:22:31 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/08/26 23:23:34 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_bonus.h"

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

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**env_to_array(t_env *env)
{
	char	**envp;
	char	*temp;
	t_env	*tmp;
	int		count;
	int		i;

	count = count_and_allocate(env, &envp);
	if (count == -1)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp && i < count)
	{
		if (tmp->value)
		{
			temp = rb_strjoin(tmp->key, "=");
			envp[i] = rb_strjoin(temp, tmp->value);
			free(temp);
			i++;
		}
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
