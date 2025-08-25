/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 23:40:12 by redadgh           #+#    #+#             */
/*   Updated: 2025/08/25 23:13:02 by mdaghouj         ###   ########.fr       */
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