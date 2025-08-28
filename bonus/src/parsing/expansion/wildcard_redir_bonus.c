/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_redir_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 03:01:48 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/08/28 03:27:06 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_bonus.h"

bool	is_valid_match(char *entry_name, char *pattern)
{
	if (entry_name[0] == '.')
		return (false);
	return (is_match(entry_name, pattern));
}

char	*scan_matches(DIR *dir, char *pattern)
{
	int				count;
	char			*matched;
	struct dirent	*entry;

	count = 0;
	matched = NULL;
	entry = readdir(dir);
	while (entry)
	{
		if (is_valid_match(entry->d_name, pattern))
		{
			count++;
			if (count == 1)
				matched = ft_strdup(entry->d_name);
			else if (count == 2)
			{
				matched = ft_strjoin(matched, " ");
				matched = ft_strjoin(matched, entry->d_name);
				break ;
			}
		}
		entry = readdir(dir);
	}
	return (matched);
}

int	expand_wildcards_redir(t_redir *redir)
{
	DIR				*dir;
	char			*matched;

	dir = opendir(".");
	if (!dir)
		return (EXIT_FAILURE);
	matched = scan_matches(dir, redir->file_delim);
	if (matched)
	{
		free(redir->file_delim);
		redir->file_delim = matched;
	}
	closedir(dir);
	return (EXIT_SUCCESS);
}
