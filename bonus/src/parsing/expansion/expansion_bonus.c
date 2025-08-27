/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:34:14 by redadgh           #+#    #+#             */
/*   Updated: 2025/08/27 19:44:34 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_bonus.h"

void	expander_magic(t_expander *exp, char *value, int *i, t_shell *shell)
{
	char	*exit_status;

	exp->start_pos = ++(*i);
	if (value[*i] == '?')
	{
		exit_status = ft_itoa(shell->exit_status);
		exp->output = ft_strjoin(exp->output, exit_status);
		free(exit_status);
	}
	else
	{
		while (ft_isalnum(value[*i]) || value[*i] == '_')
			(*i)++;
		exp->var = ft_substr(value, exp->start_pos, *i - exp->start_pos);
		exp->var = get_env_value(exp->var, shell->env);
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

char	*expand_var(char *value, t_shell *shell)
{
	t_expander	exp;
	int			i;

	i = 0;
	init_expander(&exp);
	while (value[i])
	{
		if (value[i] == SQUOTE && !exp.dquote)
			handle_quotes(&exp, value[i], true);
		else if (value[i] == DQUOTE && !exp.squote)
			handle_quotes(&exp, value[i], false);
		else if (is_valid_to_expand(value[i], value[i + 1], exp.squote))
			expander_magic(&exp, value, &i, shell);
		else
			skip_and_join(&exp, value, &i);
		i++;
	}
	free(value);
	return (exp.output);
}

void	expand_redir(t_redir *redir, t_shell *shell)
{
	while (redir)
	{
		if (redir->type != TOKEN_HEREDOC)
			redir->file_delim = expand_var(redir->file_delim, shell);
		else if (redir->type == TOKEN_HEREDOC)
			should_heredoc_expand(redir);
		redir = redir->next;
	}
}

void	expansion(t_shell *shell)
{
	int		i;
	char	*exp_value;
	t_cmd	*ptr;

	ptr = shell->cmd;
	while (ptr)
	{
		i = 0;
		while (ptr->args[i])
		{
			exp_value = expand_var(ptr->args[i], shell);
			if (should_split(exp_value, false, false, false))
				ptr->args = append_args(ptr->args, exp_value, &i, 0);
			else
			{
				ptr->args[i] = exp_value;
				i++;
			}
		}
		expand_redir(ptr->redir, shell);
		expand_wildcards(ptr);
		ptr = ptr->next;
	}
	quote_cleaner(shell->cmd);
}
