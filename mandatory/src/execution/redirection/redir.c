#include "../../../include/minishell.h"

static int	handle_input_redir(t_redir *redir)
{
	int	fd;

	if (redir->type == REDIR_HEREDOC)
	{
		if(dup2(redir->heredoc_fd, STDIN_FILENO) == -1)
			return (perror("dup2"), -1);
		close(redir->heredoc_fd);
	}
	else if (redir->type == REDIR_INPUT)
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

	if (redir->type == REDIR_OUTPUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (redir->type == REDIR_APPEND)
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

int	setup_redirections(t_cmd *cmd)
{
	t_redir	*current;

	if (!cmd || cmd->redir)
		return (0);
	current = cmd->redir;
	while (current)
	{
		if (current->type == REDIR_INPUT || current->type == REDIR_HEREDOC)
		{
			if (handle_input_redir(current) == -1)
				return (-1);
		}
		else if (current->type == REDIR_OUTPUT || current->type == REDIR_APPEND)
		{
			if (handle_output_redir(current) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
