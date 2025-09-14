/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:05:03 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/09/14 11:19:25 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_bonus.h"

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

void	generate_prompt(char **prompt, t_env *env)
{
	char	cwd[1024];
	char	*username;

	*prompt = ft_strdup(GREEN);
	username = get_env_value(ft_strdup("USER"), env);
	if (!username)
		username = ft_strdup("unknown");
	*prompt = ft_strjoin(*prompt, username);
	*prompt = ft_strjoin(*prompt, RESET"@"YELLOW"shellnobyl"RESET":"BLUE);
	if (getcwd(cwd, sizeof(cwd)))
		*prompt = ft_strjoin(*prompt, cwd);
	else
		*prompt = ft_strjoin(*prompt, "?");
	*prompt = ft_strjoin(*prompt, RESET"$ ");
	if (!ft_strcmp(username, "unknown"))
		free(username);
}
