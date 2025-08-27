/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 23:44:35 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/08/28 00:38:14 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_bonus.h"

bool	is_match(char *str, char *pattern)
{
	if (*pattern == '\0')
		return (*str == '\0');
	if (*pattern == '*')
	{
		if (*str && is_match(str + 1, pattern))
			return (true);
		return (is_match(str, pattern + 1));
	}
	if (*str && *pattern == *str)
		return (is_match(str + 1, pattern + 1));
	return (false);
}

char	**add_matched_args(char *value, char **matched_args)
{
	char	**new_args;
	int		len;
	int		i;

	i = 0;
	len = get_args_count(matched_args);
	new_args = (char **)malloc((len + 2) * sizeof (char *));
	if (!new_args)
		return (NULL);
	while (i < len && matched_args)
	{
		new_args[i] = matched_args[i];
		i++;
	}
	new_args[i] = ft_strdup(value);
	new_args[i + 1] = NULL;
	free(matched_args);
	return (new_args);
}

char	**updated_args(char **args, char **matched_args, int *pos)
{
	char	**new_args;
	int		len;
	int		i;
	int		j;

	i = -1;
	j = 1;
	len = get_args_count(args) + get_args_count(matched_args);
	new_args = (char **)malloc((len + 1) * sizeof (char *));
	if (!new_args)
		return (NULL);
	while (++i < *pos)
		new_args[i] = args[i];
	len = 0;
	while (matched_args[len])
		new_args[i++] = matched_args[len++];
	while (args[*pos + j])
		new_args[i++] = args[*pos + j++];
	new_args[i] = NULL;
	free(args[*pos]);
	*pos += get_args_count(matched_args) - 1;
	free(args);
	free(matched_args);
	return (new_args);
}

char	**get_matching_files(char **args, char *pattern, int *pos)
{
	struct dirent	*entry;
	DIR				*dir;
	char			**matched_args;

	matched_args = NULL;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.')
		{
			if (is_match(entry->d_name, pattern))
				matched_args = add_matched_args(entry->d_name, matched_args);
		}
		entry = readdir(dir);
	}
	if (matched_args)
		args = updated_args(args, matched_args, pos);
	closedir(dir);
	return (args);
}

int	expand_wildcards(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		if (ft_strchr(cmd->args[i], '*'))
		{
			cmd->args = get_matching_files(cmd->args, cmd->args[i], &i);
			if (!cmd->args)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
