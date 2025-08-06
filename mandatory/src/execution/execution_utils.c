/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-ais <rben-ais@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:35:40 by redadgh           #+#    #+#             */
/*   Updated: 2025/08/06 19:56:36 by rben-ais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	is_builtin(char *cmd)
{
	if (!cmd)
		return(0);
	if (!ft_strcmp(cmd, "echo")
	||	!ft_strcmp(cmd, "cd")
	||	!ft_strcmp(cmd, "pwd")
	||	!ft_strcmp(cmd, "export")
	||	!ft_strcmp(cmd, "unset")
	||	!ft_strcmp(cmd, "env")
	||	!ft_strcmp(cmd, "exit"))
		return(1);
	else
		return (0);
}

static char *search_in_paths(char **paths, char *cmd)
{
	char	*full_path;
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = rb_strjoin(paths[i], "/");
		if (!tmp)
		{
			i++;
			continue;
		}
		full_path = rb_strjoin(tmp, cmd);
		free(tmp);
		if (!full_path)
		{
			i++;
			continue;
		}
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
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
	path_env = rb_get_env_value(ft_strdup("PATH"), env);
	if (ft_strchr(cmd, '/') || path_env == NULL)
	{
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == 0)
				return (ft_strdup(cmd));
			return(NULL); // bdlha l permetion denied 
		}
		return (NULL);
	}
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return(NULL);
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
		return (-1);
	return (count);
}