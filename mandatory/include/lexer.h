/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reda <reda@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:52:40 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/06/05 14:34:39 by reda             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

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

void	lexer(char *input, t_token **list);
int		is_append_out(char *input);
int		is_heredoc(char *input);
int		is_redir_out(char c);
int		is_redir_in(char c);
int		is_pipe(char c);
t_token	*ft_lstnew_token(char *value);
t_token	*ft_lstlast_token(t_token *lst);
void	ft_lstclear_token(t_token **lst);
void	ft_lstadd_back_token(t_token **lst, t_token *node);

#endif