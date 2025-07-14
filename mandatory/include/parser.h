/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:46:12 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/07/14 02:14:29 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

# define SYNTAX_MSG "shellnobyl: syntax error near unexpected token `newline'\n"

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

int		check_syntax(t_token *list);
int		unclosed_quotes(char *value);
int		empty_pipe(t_token *prev_toke, unsigned int type, t_token *token);
int		invalid_redir(unsigned int type, t_token *next);
void	parser(t_token *list, t_cmd **cmd);
t_cmd	*ft_lstnew_cmd(char **args);
t_cmd	*ft_lstlast_cmd(t_cmd *lst);
void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *node);
t_redir	*ft_lstnew_redir(unsigned int type, char *file_delim);
t_redir	*ft_lstlast_redir(t_redir *lst);
void	ft_lstadd_back_redir(t_redir **lst, t_redir *node);
void	ft_lstclear_cmd(t_cmd **lst);
void	fill_redir(t_token *list, t_cmd **node, int redir_nbr);

#endif