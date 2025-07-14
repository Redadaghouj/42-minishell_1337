/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:00:29 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/14 14:16:27 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "parser.h"
# include "env.h"

typedef struct s_expander
{
	char	*output;
	char	*var;
	int		start_pos;
	bool	squote;
	bool	dquote;
}	t_expander;

/* EXPANSION */
void	expansion(t_env *env_lst, t_cmd *cmd);
void	expander_magic(t_expander *exp, char *value, int *i, t_env *env);

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

#endif