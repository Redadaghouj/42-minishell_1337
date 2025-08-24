/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 23:39:46 by redadgh           #+#    #+#             */
/*   Updated: 2025/08/24 22:02:24 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	should_heredoc_expand(t_redir *node)
{
	char	*value;

	value = node->file_delim;
	if (ft_strchr(value, '"') || ft_strchr(value, '\''))
		node->should_expand = false;
}

char	*expand_heredoc(char *line, t_shell *shell)
{
	t_expander	exp;
	int			i;

	i = 0;
	init_expander(&exp);
	while (line[i])
	{
		if (line[i] == '$' && (ft_isalpha(line[i + 1]) || line[i + 1] == '_'))
			expander_magic(&exp, line, &i, shell);
		else
			exp.output = append_char(exp.output, line[i]);
		i++;
	}
	free(line);
	return (exp.output);
}

void	child_process(t_redir *node, t_shell *shell)
{
	char	*line;
	int		fd;

	setup_heredoc_signals();
	fd = open(HEREDOC_TMP, O_CREAT | O_RDWR | O_TRUNC, 0644);
	node->file_delim = ft_strjoin(node->file_delim, "\n");
	while (true)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		line = ft_strjoin(line, "\n");
		if (!line || !ft_strcmp(line, node->file_delim))
		{
			if (!line)
				ft_putstr_fd("\n", STDOUT_FILENO);
			free(line);
			break ;
		}
		if (node->should_expand)
			line = expand_heredoc(line, shell);
		ft_putstr_fd(line, fd);
		free(line);
	}
	close(fd);
	exit(EXIT_SUCCESS);
}

int	run_heredoc(t_redir *node, t_shell *shell)
{
	int		status;
	pid_t	pid;

	ignore_sigint_main_signal();
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0)
		child_process(node, shell);
	else
	{
		waitpid(pid, &status, 0);
		setup_main_signals();
		if (WEXITSTATUS(status) == EXIT_SIGINT)
		{
			shell->exit_status = EXIT_SIGINT;
			unlink(HEREDOC_TMP);
			return (EXIT_FAILURE);
		}
		node->heredoc_fd = open(HEREDOC_TMP, O_RDONLY);
		unlink(HEREDOC_TMP);
		shell->exit_status = EXIT_SUCCESS;
	}
	return (EXIT_SUCCESS);
}

int	handle_heredoc(t_shell *shell)
{
	t_redir	*redir;
	t_cmd	*cmd;

	cmd = shell->cmd;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type == TOKEN_HEREDOC && run_heredoc(redir, shell))
				return (EXIT_FAILURE);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (EXIT_SUCCESS);
}
