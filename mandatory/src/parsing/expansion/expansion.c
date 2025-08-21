/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-ais <rben-ais@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:34:14 by redadgh           #+#    #+#             */
/*   Updated: 2025/08/21 12:36:10 by rben-ais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	expander_magic(t_expander *exp, char *value, int *i, t_env *env)
{
	exp->start_pos = ++(*i);
	if (value[*i] == '?')
		exp->output = ft_strjoin(exp->output, "0");
	else
	{
		while (ft_isalnum(value[*i]) || value[*i] == '_')
			(*i)++;
		exp->var = ft_substr(value, exp->start_pos, *i - exp->start_pos);
		exp->var = get_env_value(exp->var, env);
		if (exp->var)
			exp->output = ft_strjoin(exp->output, exp->var);
		(*i)--;
	}
}

void	skip_and_join(t_expander *exp, char *value, int *i)
{
	if (value[*i] == '$' && !exp->dquote && !exp->squote)
	{
		if (ft_isdigit(value[*i + 1]))
			*i += 2;
		else if (value[*i + 1] == SQUOTE || value[*i + 1] == DQUOTE)
			*i += 1;
	}
	exp->output = append_char(exp->output, value[*i]);
}

char	*expand_var(char *value, t_env *env_lst)
{
	t_expander	exp;
	int			i;

	i = 0;
	init_expander(&exp);
	while (value[i])
	{
		if (value[i] == SQUOTE && !exp.dquote)
			handle_quotes(&exp, value[i], true);
		else if (value[i] == '\"' && !exp.squote)
			handle_quotes(&exp, value[i], false);
		else if (is_valid_to_expand(value[i], value[i + 1], exp.squote))
			expander_magic(&exp, value, &i, env_lst);
		else
			skip_and_join(&exp, value, &i);
		i++;
	}
	free(value);
	return (exp.output);
}

void	expand_redir(t_redir *redir, t_env *env_lst)
{
	while (redir)
	{
		if (redir->type != TOKEN_HEREDOC)
			redir->file_delim = expand_var(redir->file_delim, env_lst);
		else if (redir->type == TOKEN_HEREDOC)
			should_heredoc_expand(redir);
		redir = redir->next;
	}
}

void	expansion(t_env *env_lst, t_cmd *cmd)
{
	int		i;
	char	*exp_value;
	t_cmd	*ptr;

	ptr = cmd;
	while (ptr)
	{
		i = 0;
		while (ptr->args[i])
		{
			exp_value = expand_var(ptr->args[i], env_lst);
			if (should_split(exp_value, false, false, false))
				ptr->args = append_args(ptr->args, exp_value, &i, 0);
			else
				ptr->args[i] = exp_value;
			i++;
		}
		expand_redir(ptr->redir, env_lst);
		ptr = ptr->next;
	}
	quote_cleaner(cmd);
}
