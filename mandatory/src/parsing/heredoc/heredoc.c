/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-ais <rben-ais@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 23:39:46 by redadgh           #+#    #+#             */
/*   Updated: 2025/08/20 22:31:28 by rben-ais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	should_heredoc_expand(t_redir *node)
{
	char	*value;
	int		len;

	value = node->file_delim;
	len = ft_strlen(value) - 1;
	if (value[0] == '"' && value[1] == '"')
		node->should_expand = false;
	else if (value[len] == '"' && value[len - 1] == '"')
		node->should_expand = false;
	else if (value[0] == '\'' && value[1] == '\'')
		node->should_expand = false;
	else if (value[len] == '\'' && value[len - 1] == '\'')
		node->should_expand = false;
}

char	*expand_heredoc(char *line, t_env *env_lst)
{
	t_expander	exp;
	int			i;

	i = 0;
	init_expander(&exp);
	while (line[i])
	{
		if (line[i] == '$' && (ft_isalpha(line[i + 1]) || line[i + 1] == '_'))
			expander_magic(&exp, line, &i, env_lst);
		else
			exp.output = append_char(exp.output, line[i]);
		i++;
	}
	free(line);
	return (exp.output);
}

void	child_process(t_redir *node, t_env *env)
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
		if (!line || ft_strcmp(line, node->file_delim) == 0)
		{
			if (!line)
				ft_putstr_fd("\n", STDOUT_FILENO);
			free(line);
			break ;
		}
		if (node->should_expand)
			line = expand_heredoc(line, env);
		ft_putstr_fd(line, fd);
		free(line);
	}
	close(fd);
	exit(EXIT_SUCCESS);
}

int	run_heredoc(t_redir *node, t_env *env)
{
	int		status;
	pid_t	pid;

	ignore_sigint_main_signal();
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0)
		child_process(node, env);
	else
	{
		waitpid(pid, &status, 0);
		setup_main_signals();
		if (WEXITSTATUS(status) == SIGINT_KILLED)
		{
			unlink(HEREDOC_TMP);
			return (EXIT_FAILURE);
		}
		node->heredoc_fd = open(HEREDOC_TMP, O_RDONLY);
		unlink(HEREDOC_TMP);
	}
	return (EXIT_SUCCESS);
}

int	handle_heredoc(t_cmd *cmd, t_env *env)
{
	t_redir	*redir;

	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type == TOKEN_HEREDOC && run_heredoc(redir, env))
				return (EXIT_FAILURE);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (EXIT_SUCCESS);
}
