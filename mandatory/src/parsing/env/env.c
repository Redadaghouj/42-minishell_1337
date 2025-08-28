/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 21:31:17 by redadgh           #+#    #+#             */
/*   Updated: 2025/08/28 18:21:32 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_env	*init_env(void)
{
	t_env	*env;

	env = NULL;
	env = parse_env();
	if (!env)
	{
		env = (t_env *)malloc(sizeof(t_env));
		if (!env)
			return (NULL);
		env->key = ft_strdup(ENV_PATH_KEY);
		env->value = ft_strdup(DEFAULT_PATH);
		env->next = NULL;
	}
	return (env);
}

t_env	*parse_env(void)
{
	int		i;
	char	*sign;
	t_env	*env_list;
	t_env	*node;

	i = 0;
	env_list = NULL;
	while (environ[i])
	{
		sign = ft_strchr(environ[i], '=');
		if (sign)
		{
			node = ft_lstnew_env(ft_strdup(sign + 1),
					ft_substr(environ[i], 0, sign - environ[i]));
			if (!node)
			{
				ft_lstclear_env(&env_list);
				return (NULL);
			}
			ft_lstadd_back_env(&env_list, node);
		}
		i++;
	}
	return (env_list);
}

char	*get_env_value(char *var, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(var, env->key) == 0)
		{
			free(var);
			return (env->value);
		}
		env = env->next;
	}
	free(var);
	return (NULL);
}
