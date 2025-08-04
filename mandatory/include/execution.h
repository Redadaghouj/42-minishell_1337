/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-ais <rben-ais@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:34:46 by redadgh           #+#    #+#             */
/*   Updated: 2025/08/04 05:39:06 by rben-ais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "env.h"
# include "minishell.h"

void	execution(t_env **env, t_cmd *cmd);

//builtins :
void	ft_echo(char **arv);
void	ft_pwd(void);
void	ft_env(t_env **env);
void    ft_cd(char **args, t_env **env);
void    ft_exit(char **args);
void	ft_export(char **args, t_env **env);
void	ft_unset(char **args, t_env **env);

//utils
int     is_valid_identifier(char *str);
int     is_builtin(char *cmd);
#endif