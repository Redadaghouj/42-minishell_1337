/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-ais <rben-ais@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:34:46 by redadgh           #+#    #+#             */
/*   Updated: 2025/08/08 13:55:49 by rben-ais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# define REDIR_INPUT	1
# define REDIR_OUTPUT	2
# define REDIR_APPEND	3
# define REDIR_HEREDOC	4

# include "env.h"
# include "parser.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

void	execution(t_env **env, t_cmd *cmd);
int     setup_redirections(t_cmd *cmd);

//builtins :
void	ft_export(char **args, t_env **env);
void	ft_unset(char **args, t_env **env);
void    ft_cd(char **args, t_env **env);
void    ft_exit(char **args);
void	ft_echo(char **arv);
void	ft_env(t_env **env);
void	ft_pwd(void);

//utils
int     count_and_allocate(t_env *env, char ***envp);
char	*find_command_path(char *cmd, t_env *env);
int     is_valid_identifier(char *str);
void	free_array(char **array);
int     is_builtin(char *cmd);

#endif