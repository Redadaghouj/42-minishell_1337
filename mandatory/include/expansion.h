/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:00:29 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/14 02:08:09 by redadgh          ###   ########.fr       */
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

void	expansion(t_env *env_lst, t_cmd *cmd);
void	init_expander(t_expander *expand);
char	*append_char(char *s1, char c);
int		ft_isalnum(int c);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
bool	is_valid_to_expand(char current, char next, bool squote);
void	expander_magic(t_expander *exp, char *value, int *i, t_env *env);
void	handle_quotes(t_expander *exp, char c, bool squote);
bool	should_split(char *exp_value, bool space, bool squote, bool dquote);
char	**append_args(char **args, char *value, int *pos, int j);
bool	is_redir(char *value);
char	*add_quotes(char *value);
void	quote_cleaner(t_cmd *cmd);

#endif