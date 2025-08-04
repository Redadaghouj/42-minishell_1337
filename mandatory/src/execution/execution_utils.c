/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-ais <rben-ais@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:35:40 by redadgh           #+#    #+#             */
/*   Updated: 2025/08/04 06:05:54 by rben-ais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

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
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = build_full_path(paths[i], cmd);
		if (!full_path)
		{
			i++;
			continue;
		}
		if (accses(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
}

char	*find_command_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*path_env;
	char	*result;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = get_env_value("PATH", env);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return(NULL);
	result = search_in_path(paths, cmd);
	free_array(paths);
	return (result);
}
