/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-ais <rben-ais@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:05:03 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/08/25 17:36:47 by rben-ais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	setup_main_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, NULL);
}

int	is_eof_input(t_shell *shell, char *input)
{
	if (!input)
	{
		shell->exit_status = EXIT_SUCCESS;
		printf("exit\n");
		free(input);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	*free_buffer(char **buffer)
{
	int	i;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] != NULL)
	{
		free(buffer[i]);
		i++;
	}
	free(buffer);
	return (NULL);
}

t_env	*init_env(void)
{
	t_env	*env;

	env = NULL;
	env = parse_env();
	if (!env)
	{
		env = (t_env *)malloc(sizeof(t_env));
		if (!env)
			return (NULL);
		env->key = ft_strdup(ENV_PATH_KEY);
		env->value = ft_strdup(DEFAULT_PATH);
		env->next = NULL;
	}
	return (env);
}
