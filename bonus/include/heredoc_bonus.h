/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 23:40:12 by redadgh           #+#    #+#             */
/*   Updated: 2025/08/27 19:16:01 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_BONUS_H
# define HEREDOC_BONUS_H

# include <fcntl.h>
# include <sys/wait.h>

# include "expansion_bonus.h"

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