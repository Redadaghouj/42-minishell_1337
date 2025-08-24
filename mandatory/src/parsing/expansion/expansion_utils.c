/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:34:26 by redadgh           #+#    #+#             */
/*   Updated: 2025/08/24 03:06:53 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool	should_expand(bool squote)
{
	return (!squote);
}

void	init_expander(t_expander *exp)
{
	exp->output = ft_strdup("");
	exp->var = NULL;
	exp->squote = false;
	exp->dquote = false;
	exp->start_pos = 0;
}

bool	is_valid_to_expand(char current, char next, bool squote)
{
	if (current == '$')
	{
		if (should_expand(squote) && (ft_isalpha(next) || next == '_' || next == '?'))
			return (true);
	}
	return (false);
}

void	handle_quotes(t_expander *exp, char c, bool squote)
{
	if (squote)
		exp->squote = !exp->squote;
	else
		exp->dquote = !exp->dquote;
	exp->output = append_char(exp->output, c);
}

char	*append_char(char *s1, char c)
{
	char	*str;
	int		i;

	i = -1;
	if (!s1)
		return (NULL);
	str = malloc((ft_strlen(s1) + 3) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	str[i++] = c;
	str[i] = '\0';
	free(s1);
	return (str);
}
