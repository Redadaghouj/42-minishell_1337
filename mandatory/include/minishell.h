/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:33:47 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/07/14 14:30:44 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <stdbool.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "lexer.h"
# include "parser.h"
# include "expansion.h"
# include "env.h"
# include "heredoc.h"

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

extern char	**environ;

/* UTILS */
int		ft_strcmp(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
void	*free_buffer(char **buffer);
char	**ft_split(char const *s, char c);
void	ft_putstr_fd(char *s, int fd);
int		ft_isalnum(int c);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
char	*gnl(int fd, int i);

/* MINISHELL UTILS */
int		ends_prompt_loop(char *input);
void	handle_sigint(int sig);
int		setup_lists(t_token **token, t_env **env, t_cmd **cmd);
void	setup_signals(void);

void	print_cmd_list(t_cmd *cmd); // CHECK:

#endif