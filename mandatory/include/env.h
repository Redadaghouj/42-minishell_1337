/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:03:39 by redadgh           #+#    #+#             */
/*   Updated: 2025/08/25 16:49:41 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# define ENV_PATH_KEY "PATH"
# define DEFAULT_PATH "/bin:/usr/bin"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/* ENV */
char	*get_env_value(char *var, t_env *env);
char	*rb_get_env_value(char *var, t_env *env);
t_env	*parse_env(void);

/* ENV LISTS */
t_env	*ft_lstnew_env(char *value, char *key);
t_env	*ft_lstlast_env(t_env *lst);
void	ft_lstclear_env(t_env **lst);
void	ft_lstadd_back_env(t_env **lst, t_env *node);

#endif