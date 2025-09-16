/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:23:35 by rben-ais          #+#    #+#             */
/*   Updated: 2025/09/16 10:03:37 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell_bonus.h"

static void	remove_env_variable(char *key, t_env **env)
{
	t_env	*current;
	t_env	*prev;

	if (!env || !*env)
		return ;
	current = *env;
	prev = NULL;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			if (current->value)
				free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

static void	unset_variable(char *arg, t_shell *shell)
{
	if (is_valid_identifier(arg))
	{
		shell->exit_status = EXIT_SUCCESS;
		remove_env_variable(arg, &shell->env);
	}
	else
	{
		shell->exit_status = EXIT_FAILURE;
		builtin_err("unset: `", arg, "': not a valid identifier\n");
	}
}

void	ft_unset(t_shell *shell, char **args)
{
	int	i;

	if (!shell || !shell->env || !args || !args[1])
		return ;
	i = 1;
	while (args[i])
	{
		unset_variable(args[i], shell);
		i++;
	}
}
