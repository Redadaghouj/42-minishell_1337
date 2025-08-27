/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:52:40 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/08/26 23:31:10 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_BONUS_H
# define LEXER_BONUS_H

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND_OUT,
	TOKEN_HEREDOC
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

/* TOKENIZE INPUT */
void	lexer(char *input, t_token **list);

/* TOKENIZE LISTS */
t_token	*ft_lstnew_token(char *value);
t_token	*ft_lstlast_token(t_token *lst);
void	ft_lstclear_token(t_token **lst);
void	ft_lstadd_back_token(t_token **lst, t_token *node);

/* CHECK OPERATOR */
int		is_append_out(char *input);
int		is_heredoc(char *input);
int		is_redir_out(char c);
int		is_redir_in(char c);
int		is_pipe(char c);

#endif