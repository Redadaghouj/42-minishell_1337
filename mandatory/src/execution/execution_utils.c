/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:35:40 by redadgh           #+#    #+#             */
/*   Updated: 2025/08/25 23:19:29 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (1);
	else
		return (0);
}

static char	*join_and_check(char *path, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = rb_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	full_path = rb_strjoin(tmp, cmd);
	free(tmp);
	if (!full_path)
		return (NULL);
	if (access(full_path, F_OK | X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

static char	*search_in_paths(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = join_and_check(paths[i], cmd);
		if (full_path)
			return (full_path);
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*path_env;
	char	*result;

	if (!cmd)
		return (NULL);
	path_env = get_env_value(ft_strdup("PATH"), env);
	if (ft_strchr(cmd, '/') || path_env == NULL)
	{
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == 0)
				return (ft_strdup(cmd));
			return (NULL);
		}
		return (NULL);
	}
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	result = search_in_paths(paths, cmd);
	free_array(paths);
	return (result);
}

int	count_and_allocate(t_env *env, char ***envp)
{
	t_env	*tmp;
	int		count;

	count = 0;
	tmp = env;
	while (tmp)
	{
		if (tmp->value)
			count++;
		tmp = tmp->next;
	}
	*envp = (char **)malloc((count + 1) * sizeof(char *));
	if (!*envp)
	{
		free(*envp);
		return (-1);
	}
	return (count);
}
