/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 23:44:35 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/08/27 20:02:34 by mdaghouj         ###   ########.fr       */
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

void	get_matching_files(char *pattern)
{
	struct dirent	*entry;
	DIR				*dir;

	dir = opendir(".");
	if (!dir)
		return ;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.')
		{
			if (is_match(entry->d_name, pattern))
				printf("%s\n", entry->d_name);
		}
		entry = readdir(dir);
	}
	closedir(dir);
}

int	expand_wildcards(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		if (ft_strchr(cmd->args[i], '*'))
		{
			get_matching_files(cmd->args[i]);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
