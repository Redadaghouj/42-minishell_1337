/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 23:40:12 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/15 19:06:25 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include <fcntl.h>
# include <sys/wait.h>
# include "expansion.h"

# define HEREDOC_TMP "/tmp/.minishell_heredoc.tmp"
# define SIGINT_KILLED 130

/* HEREDOC */
void	should_heredoc_expand(t_redir *node);
int		handle_heredoc(t_cmd *cmd, t_env *env);

/* HEREDOC SIGNALS */
void	handle_heredoc_sigint(int signum);
void	setup_heredoc_signals(void);
void	ignore_sigint_main_signal(void);

#endif