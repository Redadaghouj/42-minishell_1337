/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-ais <rben-ais@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:34:46 by redadgh           #+#    #+#             */
/*   Updated: 2025/08/21 13:42:54 by rben-ais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "env.h"
# include "parser.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

# define ERR_AMBIGUOUS_REDIRECT \
		"Shellnobyl: ambiguous redirect\n"

void	execution(t_env **env, t_cmd *cmd);
void	exec_builtin(t_env **env, t_cmd *cmd);
void	exec_external_child(t_env **env, t_cmd *cmd);
int		setup_redirection(t_cmd *cmd);
void	execute_pipeline(t_env **env, t_cmd *cmd_list);
//builtins :
void	ft_export(char **args, t_env **env);
void	ft_unset(char **args, t_env **env);
void	ft_cd(char **args, t_env **env);
void	ft_exit(char **args);
void	ft_echo(char **arv);
void	ft_env(t_env **env);
void	ft_pwd(void);

//utils
int		count_and_allocate(t_env *env, char ***envp);
char	*find_command_path(char *cmd, t_env *env);
int		is_valid_identifier(char *str);
void	free_array(char **array);
int		is_builtin(char *cmd);

/* AMBIGUOUS REDIR */
bool	is_redir_ambiguous(t_redir *redir);

#endif