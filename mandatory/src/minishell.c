/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rben-ais <rben-ais@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:26:52 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/08/21 13:32:41 by rben-ais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_status;

// g_exit_status = 0;
void	cleanup_resources(t_token **token, t_cmd **cmd, char *input)
{
	ft_lstclear_token(token);
	ft_lstclear_cmd(cmd);
	free(input);
}

void	process_line(char *input, t_env **env)
{
	t_token	*token;
	t_cmd	*cmd;

	token = NULL;
	cmd = NULL;
	lexer(input, &token);
	parser(token, &cmd);
	expansion(*env, cmd);
	handle_heredoc(cmd, *env);
	execution(env, cmd);
	cleanup_resources(&token, &cmd, input);
}

void	run_interactive_shell(t_env **env)
{
	char	*input;

	setup_main_signals();
	while (true)
	{
		input = readline("☢️ shellnobyl$ ");
		if (should_terminate_prompt(input))
			break ;
		if (*input)
		{
			add_history(input);
			process_line(input, env);
		}
	}
}

void	run_script_shell(t_env **env)
{
	char	*input;

	while (true)
	{
		input = get_next_line(STDIN_FILENO);
		if (!input)
			break ;
		process_line(input, env);
	}
}

int	main(void)
{
	t_env	*env;

	env = init_env();
	if (!env)
		return (EXIT_FAILURE);
	else if (isatty(STDIN_FILENO))
		run_interactive_shell(&env);
	else
		run_script_shell(&env);
	ft_lstclear_env(&env);
	return (EXIT_SUCCESS);
}
