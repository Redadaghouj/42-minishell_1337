/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:22:30 by rben-ais          #+#    #+#             */
/*   Updated: 2025/08/24 20:43:42 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	print_export_format(t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
	shell->exit_status = EXIT_SUCCESS;
}

int	is_valid_identifier(char *str)
{
	int i;
	
	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	handle_assignment(char *key, char *value, t_env **env)
{
	t_env	*current;
	t_env	*new_node;

	current = *env;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
		{
			if (current->value)
				free(current->value);
			current->value = ft_strdup(value);
		}
		current = current->next;
	}
	new_node = ft_lstnew_env(ft_strdup(value), ft_strdup(key));
	if (new_node)
		ft_lstadd_back_env(env, new_node);
}

static void	export_variable(char *arg, t_shell *shell)
{
	char	*equal_sign_string;
	char	*key;
	char	*value;
	
	equal_sign_string = ft_strchr(arg, '=');
	shell->exit_status = EXIT_FAILURE;
	if (equal_sign_string)
	{
		key = ft_substr(arg, 0, equal_sign_string - arg);
		value = ft_strdup(equal_sign_string + 1);
		if (is_valid_identifier(key))
		{
			shell->exit_status = EXIT_SUCCESS;
			handle_assignment(key, value, &shell->env);
		}
		else
			printf("Shellnobyl: export: `%s': not a valid identifier\n", arg);
		free(key);
		free(value);
	}
	else
		if (!is_valid_identifier(arg))
			printf ("Shellnobyl: export: `%s': not a valid identifier", arg);
}

void	ft_export(t_shell *shell, char **args)
{
	int		i;

	if (!shell || !shell->env || !args)
		return;
	if (!args[1])
	{
		print_export_format(shell);
		return;
	}
	i = 1;
	while (args[i])
	{
		export_variable(args[i], shell);
		i++;
	}
}
