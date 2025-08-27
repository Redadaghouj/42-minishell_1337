/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:56:58 by rben-ais          #+#    #+#             */
/*   Updated: 2025/08/26 23:20:07 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_bonus.h"

static int	handle_input_redir(t_redir *redir)
{
	int	fd;

	if (redir->type == TOKEN_HEREDOC)
	{
		if (dup2(redir->heredoc_fd, STDIN_FILENO) == -1)
			return (perror("dup2"), -1);
		close(redir->heredoc_fd);
	}
	else if (redir->type == TOKEN_REDIR_IN)
	{
		fd = open(redir->file_delim, O_RDONLY);
		if (fd == -1)
			return (perror(redir->file_delim), -1);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(fd);
			return (-1);
		}
		close (fd);
	}
	return (0);
}

static int	handle_output_redir(t_redir *redir)
{
	int	fd;
	int	flags;

	if (redir->type == TOKEN_REDIR_OUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (redir->type == TOKEN_APPEND_OUT)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		return (-1);
	fd = open(redir->file_delim, flags, 0644);
	if (fd == -1)
	{
		perror(redir->file_delim);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	setup_redirection(t_cmd *cmd)
{
	t_redir	*cur;

	if (!cmd || !cmd->redir)
		return (0);
	cur = cmd->redir;
	while (cur)
	{
		if (is_redir_ambiguous(cur))
			return (-1);
		if (cur->type == TOKEN_REDIR_IN || cur->type == TOKEN_HEREDOC)
		{
			if (handle_input_redir(cur) == -1)
				return (-1);
		}
		else if (cur->type == TOKEN_REDIR_OUT || cur->type == TOKEN_APPEND_OUT)
		{
			if (handle_output_redir(cur) == -1)
				return (-1);
		}
		cur = cur->next;
	}
	return (0);
}
