/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:05:03 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/07/13 17:52:13 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals(void)
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

int	ends_prompt_loop(char *input)
{
	if (!input || !ft_strcmp("exit", input))
	{
		printf("exit\n");
		return (1);
	}
	return (0);
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

int	setup_lists(t_token **token, t_env **env, t_cmd **cmd)
{
	*token = NULL;
	*env = NULL;
	*cmd = NULL;
	*env = parse_env();
	if (!*env)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
