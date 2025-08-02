/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-ais <rben-ais@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:22:30 by rben-ais          #+#    #+#             */
/*   Updated: 2025/08/02 18:39:43 by rben-ais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/execution.h"

static void	print_export_format(t_env *env)
{
	while (env)
	{
		if(env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
}

static void	export_variable(char *arg, t_env **env)
{
	
}

void	ft_export(char **args, t_env **env)
{
	int	i;
	
	if (!args || !env || !*env)
		return;
	if (!args[1])
	{
		printf_export_format(*env);
		return;
	}
	i = 1;
	while (args[i])
	{
		export_variable(args[i], env);
		i++;
	}
}