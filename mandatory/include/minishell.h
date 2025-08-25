/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:33:47 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/08/25 15:56:12 by mdaghouj         ###   ########.fr       */
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

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_AMBIGUOUS_REDIR 1
# define EXIT_SYNTAX 2
# define EXIT_PERMISSION 126
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_SIGNAL 128

extern char	**environ;

typedef struct s_shell
{
	t_cmd	*cmd;
	t_env	*env;
	int		exit_status;
}	t_shell;

/* MINISHELL */
void	process_line(char *input, t_shell *shell);

/* UTILS */
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
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
char	*ft_itoa(int n);
char	*get_next_line(int fd);
char	*rb_strjoin(char *s1, char *s2);

/* MINISHELL UTILS */
int		is_eof_input(t_shell *shell, char *input);
void	handle_sigint(int sig);
void	setup_main_signals(void);
t_env	*init_env(void);

#endif