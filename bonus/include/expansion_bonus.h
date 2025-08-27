/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:00:29 by redadgh           #+#    #+#             */
/*   Updated: 2025/08/27 00:33:01 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_BONUS_H
# define EXPANSION_BONUS_H

# include "parser_bonus.h"
# include "env_bonus.h"

typedef struct s_shell	t_shell;

typedef struct s_expander
{
	char	*output;
	char	*var;
	int		start_pos;
	bool	squote;
	bool	dquote;
}	t_expander;

/* EXPANSION */
void	expansion(t_shell *shell);
void	expander_magic(t_expander *exp, char *value, int *i, t_shell *shell);

/* EXPANSION UTILS */
void	init_expander(t_expander *expand);
bool	is_valid_to_expand(char current, char next, bool squote);
void	handle_quotes(t_expander *exp, char c, bool squote);
char	*append_char(char *s1, char c);

/* APPEND ARGS */
bool	should_split(char *exp_value, bool space, bool squote, bool dquote);
char	**append_args(char **args, char *value, int *pos, int j);

/* QUOTE CLEANER */
void	quote_cleaner(t_cmd *cmd);

/* WILDCARD */
void	expand_wildcards(t_cmd *cmd);

#endif