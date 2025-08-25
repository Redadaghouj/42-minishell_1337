/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-ais <rben-ais@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:34:46 by redadgh           #+#    #+#             */
/*   Updated: 2025/08/25 00:02:52 by rben-ais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "env.h"
# include "parser.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_shell	t_shell;

# define EXIT_STATUS_MASK 256
# define ERR_AMBIGUOUS_REDIRECT \
		"Shellnobyl: ambiguous redirect\n"

void	execution(t_shell *shell);
void	exec_builtin(t_shell *shell, char **args);
void	exec_external_child(t_env **env, t_cmd *cmd);
int		setup_redirection(t_cmd *cmd);
void	execute_pipeline(t_shell *shell, int prev_fd);
//builtins :
void	ft_export(t_shell *shell, char **args);
void	ft_unset(t_shell *shell, char **args);
void	ft_cd(t_shell *shell, char **args);
void	ft_exit(t_shell *shell, char **args);
void	ft_echo(t_shell *shell, char **args);
void	ft_env(t_shell *shell);
void	ft_pwd(t_shell *shell);

//utils
bool	setup_with_backup(t_cmd *cmd, int *save_stdout, int *save_stdin);
int		count_and_allocate(t_env *env, char ***envp);
char	*find_command_path(char *cmd, t_env *env);
int		is_valid_identifier(char *str);
char	**env_to_array(t_env *env);
void	free_array(char **array);
int		is_builtin(char *cmd);
/* AMBIGUOUS REDIR */
bool	is_redir_ambiguous(t_redir *redir);

#endif