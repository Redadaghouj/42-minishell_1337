/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:33:47 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/08/28 22:42:03 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <stdbool.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "lexer_bonus.h"
# include "parser_bonus.h"
# include "expansion_bonus.h"
# include "env_bonus.h"
# include "heredoc_bonus.h"
# include "execution_bonus.h"

# define RESET "\033[0m"
# define GREEN "\033[1;32m" 
# define RED "\033[1;31m"
# define BLUE "\033[1;34m"

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
void	generate_prompt(char **prompt, t_env *env);

#endif