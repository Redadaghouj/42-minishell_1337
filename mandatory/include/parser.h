/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:46:12 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/07/19 21:02:06 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

# define ERR_UNCLOSED_QUOTES \
		"Shellnobyl: unexpected EOF while looking for matching "
# define ERR_EMPTY_PIPE_UNEXPECTED_TOKEN \
		"shellnobyl: syntax error near unexpected token `|'\n"
# define ERR_EMPTY_PIPE_UNEXPECTED_EOF \
		"shellnobyl: syntax error: unexpected end of file\n"
# define ERR_INVALID_REDIR_UNEXPECTED_NEWLINE \
		"shellnobyl: syntax error near unexpected token `newline'\n"
# define ERR_INVALID_REDIR_UNEXPECTED_TOKEN \
		"shellnobyl: syntax error near unexpected token "

typedef struct s_redir
{
	char			*file_delim;
	int				heredoc_fd;
	bool			should_expand;
	unsigned int	type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redir;
	struct s_cmd	*next;
}	t_cmd;

/* PARSER */
void	parser(t_token *list, t_cmd **cmd);
void	fill_redir(t_token *list, t_cmd **node, int redir_nbr);

/* PARSER LISTS */
t_cmd	*ft_lstnew_cmd(char **args);
t_cmd	*ft_lstlast_cmd(t_cmd *lst);
void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *node);
void	ft_lstclear_cmd(t_cmd **lst);

/* CHECK SYNTAX */
int		check_syntax(t_token *list);

/* REDIR LISTS */
t_redir	*ft_lstnew_redir(unsigned int type, char *file_delim);
t_redir	*ft_lstlast_redir(t_redir *lst);
void	ft_lstadd_back_redir(t_redir **lst, t_redir *node);

#endif