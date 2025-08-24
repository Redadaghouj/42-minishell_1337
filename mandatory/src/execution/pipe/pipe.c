#include "../../../include/minishell.h"
#include <stdlib.h>

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

// static void    child_process(t_cmd *cmd, int prev_fd, int pipe_fd[2], t_env **env)
// {
//     if (prev_fd != -1)
//     {
//         dup2(prev_fd, STDIN_FILENO);
//         close(prev_fd);
//     }
//     if (cmd->next)
//     {
//         close(pipe_fd[0]);
//         dup2(pipe_fd[1], STDOUT_FILENO);
//         close(pipe_fd[1]);
//     }
//     if (setup_redirections(cmd) == -1)
//         exit(1);
    
//     if (is_builtin(cmd->args[0]))
//         exec_builtin(env, cmd);
//     else
//         exec_external_child(env, cmd);
//     exit(0);
// }

static void	child_process(t_shell *shell, t_cmd *cmd, int prev_fd, int pipe_fd[2])
{
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

void    execute_pipeline(t_shell *shell, int prev_fd)
{
    t_cmd	*cmd;
    pid_t	pid;
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
    while (wait(&status) > 0)
		shell->exit_status = WEXITSTATUS(status);
}
