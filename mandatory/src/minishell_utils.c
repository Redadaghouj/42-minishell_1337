/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:05:03 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/08/28 18:23:17 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
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

void	generate_prompt(char **prompt)
{
	char	cwd[1024];
	char	**buffer;
	int		i;

	i = 2;
	getcwd(cwd, sizeof(cwd));
	buffer = ft_split(cwd, '/');
	*prompt = ft_strjoin(ft_strdup(GREEN), buffer[1]);
	*prompt = ft_strjoin(*prompt, RESET"@");
	*prompt = ft_strjoin(*prompt, RED"shellnobyl"RESET);
	while (buffer[i] != NULL)
	{
		*prompt = ft_strjoin(*prompt, "/");
		*prompt = ft_strjoin(*prompt, BLUE);
		*prompt = ft_strjoin(*prompt, buffer[i]);
		*prompt = ft_strjoin(*prompt, RESET);
		i++;
	}
	*prompt = ft_strjoin(*prompt, "$ ");
	free_buffer(buffer);
}
