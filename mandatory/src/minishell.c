/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:26:52 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/07/17 19:07:37 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	print_cmd_list(cmd);
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
		input = gnl(STDIN_FILENO, 0);
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
