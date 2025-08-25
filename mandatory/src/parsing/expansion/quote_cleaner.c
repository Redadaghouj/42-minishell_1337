/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:31:18 by redadgh           #+#    #+#             */
/*   Updated: 2025/08/25 23:14:10 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*remove_grouping_quotes(char *val)
{
	int		i;
	int		dquote;
	int		squote;
	char	*cleaned_str;

	i = 0;
	dquote = 0;
	squote = 0;
	cleaned_str = ft_strdup("");
	while (val[i])
	{
		if (val[i] == SQUOTE && !dquote)
			squote = !squote;
		else if (val[i] == DQUOTE && !squote)
			dquote = !dquote;
		else
			cleaned_str = append_char(cleaned_str, val[i]);
		i++;
	}
	free(val);
	return (cleaned_str);
}

void	unquote_redir(t_redir *redir)
{
	while (redir)
	{
		if (redir->file_delim[0] == SQUOTE || redir->file_delim[0] == DQUOTE)
			redir->should_expand = false;
		redir->file_delim = remove_grouping_quotes(redir->file_delim);
		redir = redir->next;
	}
}

void	quote_cleaner(t_cmd *cmd)
{
	int		i;
	char	*cleaned_str;

	while (cmd)
	{
		i = 0;
		while (cmd->args[i])
		{
			cleaned_str = remove_grouping_quotes(cmd->args[i]);
			cmd->args[i] = cleaned_str;
			i++;
		}
		unquote_redir(cmd->redir);
		cmd = cmd->next;
	}
}
