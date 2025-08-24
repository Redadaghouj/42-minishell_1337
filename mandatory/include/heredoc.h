/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-ais <rben-ais@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 23:40:12 by redadgh           #+#    #+#             */
/*   Updated: 2025/08/24 01:39:09 by rben-ais         ###   ########.fr       */
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
int		handle_heredoc(t_shell *shell);
void	should_heredoc_expand(t_redir *node);

/* HEREDOC SIGNALS */
void	handle_heredoc_sigint(int signum);
void	setup_heredoc_signals(void);
void	ignore_sigint_main_signal(void);

#endif