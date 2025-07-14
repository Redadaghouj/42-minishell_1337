/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:04:55 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/09 01:26:54 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_args_count(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

bool	should_split(char *exp_value, bool space, bool squote, bool dquote)
{
	int		i;

	i = 0;
	while (exp_value[i])
	{
		if (space && !dquote && !squote)
			return (true);
		else
		{
			if (exp_value[i] == ' ')
				space = true;
			if (exp_value[i] == '\'' && !dquote)
				squote = !squote;
			else if (exp_value[i] == '"' && !squote)
				dquote = !dquote;
		}
		i++;
	}
	return (false);
}

char	**append_args(char **args, char *value, int *pos, int j)
{
	int		i;
	int		len;
	char	**new_args;
	char	**buffer;

	i = 0;
	buffer = ft_split(value, ' ');
	len = get_args_count(buffer) + get_args_count(args);
	new_args = (char **)malloc((len + 1) * sizeof (char *));
	while (i < *pos)
	{
		new_args[i] = ft_strdup(args[i]);
		free(args[i++]);
	}
	while (buffer[j])
		new_args[i++] = ft_strdup(buffer[j++]);
	j = 0;
	while (args[*pos + j++])
	{
		new_args[i++] = ft_strdup(args[*pos + j]);
		free(args[*pos + j]);
	}
	new_args[i] = NULL;
	*pos += (len - 1);
	return (free(value), free(args), free_buffer(buffer), new_args);
}
