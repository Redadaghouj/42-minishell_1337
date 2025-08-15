#include "../../../include/minishell.h"

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

static void	child_process(t_cmd *cmd, int prev_fd, int pipe_fd[2], t_env **env)
{
    int	original_stdin;
    int	original_stdout;

    // Save original file descriptors
    original_stdin = dup(STDIN_FILENO);
    original_stdout = dup(STDOUT_FILENO);

    // Handle input from previous pipe
    if (prev_fd != -1)
    {
        dup2(prev_fd, STDIN_FILENO);
        close(prev_fd);
    }

    // Handle output to next pipe
    if (cmd->next)
    {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
    }

    // Apply redirections
    if (setup_redirections(cmd) == -1)
        exit(1);

    // Execute command
    if (is_builtin(cmd->args[0]))
        exec_builtin(env, cmd);
    else
        exec_external_child(env, cmd);

    // Restore original file descriptors
    dup2(original_stdin, STDIN_FILENO);
    dup2(original_stdout, STDOUT_FILENO);
    close(original_stdin);
    close(original_stdout);

    exit(0);
}

void    execute_pipeline(t_env **env, t_cmd *cmd_list)
{
    int        pipe_fd[2];
    int        prev_fd;
    pid_t    pid;
    t_cmd    *cmd;

    prev_fd = -1;
    cmd = cmd_list;
    while (cmd)
    {
        if (cmd->next)
            pipe(pipe_fd);
        pid = fork();
        if (pid == 0)
            child_process(cmd, prev_fd, pipe_fd, env);
        if (prev_fd != -1)
            close(prev_fd);
        if (cmd->next)
        {
            close(pipe_fd[1]);
            prev_fd = pipe_fd[0];
        }
        cmd = cmd->next;
    }
    while (wait(NULL) > 0)
        ;
}