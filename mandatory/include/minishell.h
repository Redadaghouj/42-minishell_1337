/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-ais <rben-ais@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:33:47 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/08/21 13:07:41 by rben-ais         ###   ########.fr       */
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
# include "execution.h"

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
int		ft_atoi(const char *nptr);
char	*get_next_line(int fd);
char	*rb_strjoin(char *s1, char *s2);

/* MINISHELL UTILS */
int		should_terminate_prompt(char *input);
void	handle_sigint(int sig);
void	setup_main_signals(void);
t_env	*init_env(void);

void	print_cmd_list(t_cmd *cmd); // CHECK:

#endif