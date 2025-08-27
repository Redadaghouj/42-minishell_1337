/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 23:17:17 by rben-ais          #+#    #+#             */
/*   Updated: 2025/08/26 23:19:38 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_bonus.h"

void	reset_and_catch_sig(t_shell *shell, int status, bool toggle)
{
	if (toggle)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else
	{
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->exit_status = WTERMSIG(status) + EXIT_SIGNAL;
	}
}

static int	has_output_redir(t_cmd *cmd)
{
	t_redir	*redir;

	if (!cmd || !cmd->redir)
		return (0);
	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == TOKEN_REDIR_OUT || redir->type == TOKEN_APPEND_OUT)
			return (1);
		redir = redir->next;
	}
	return (0);
}

static void	child_process(t_shell *shell, t_cmd *cmd,
	int prev_fd, int pipe_fd[2])
{
	reset_and_catch_sig(shell, 0, true);
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next && !has_output_redir(cmd))
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	else if (cmd->next)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (setup_redirection(cmd) == -1)
		exit(EXIT_FAILURE);
	if (is_builtin(cmd->args[0]))
		exec_builtin(shell, cmd->args);
	else
		exec_external_child(&shell->env, cmd);
	exit(EXIT_SUCCESS);
}

void	execute_pipeline(t_shell *shell, int prev_fd, pid_t pid)
{
	t_cmd	*cmd;
	int		pipe_fd[2];
	int		status;

	cmd = shell->cmd;
	while (cmd)
	{
		if (cmd->next)
			pipe(pipe_fd);
		pid = fork();
		if (pid == 0)
			child_process(shell, cmd, prev_fd, pipe_fd);
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		cmd = cmd->next;
	}
	waitpid(pid, &status, 0);
	while (wait(NULL) > 0)
		;
	reset_and_catch_sig(shell, status, false);
}

bool	setup_with_backup(t_cmd *cmd, int *save_stdout, int *save_stdin)
{
	*save_stdout = dup(STDOUT_FILENO);
	*save_stdin = dup(STDIN_FILENO);
	if (setup_redirection(cmd) == -1)
	{
		close(*save_stdout);
		close(*save_stdin);
		return (false);
	}
	return (true);
}
