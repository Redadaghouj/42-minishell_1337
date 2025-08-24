/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:34:46 by redadgh           #+#    #+#             */
/*   Updated: 2025/08/24 06:06:17 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "env.h"
# include "parser.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

typedef struct s_shell t_shell;

# define ERR_AMBIGUOUS_REDIRECT \
		"Shellnobyl: ambiguous redirect\n"

void	execution(t_shell *shell);
void	exec_builtin(t_shell *shell);
void	exec_external_child(t_env **env, t_cmd *cmd);
int		setup_redirection(t_cmd *cmd);
void	execute_pipeline(t_shell *shell, int prev_fd);
//builtins :
void	ft_export(t_shell *shell);
void	ft_unset(t_shell *shell);
void	ft_cd(t_shell *shell);
void	ft_exit(char **args);
void	ft_echo(t_shell *shell);
void	ft_env(t_shell *shell);
void	ft_pwd(t_shell *shell);

//utils
int		count_and_allocate(t_env *env, char ***envp);
char	*find_command_path(char *cmd, t_env *env);
int		is_valid_identifier(char *str);
void	free_array(char **array);
int		is_builtin(char *cmd);

/* AMBIGUOUS REDIR */
bool	is_redir_ambiguous(t_redir *redir);

#endif