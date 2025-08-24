/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:26:52 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/08/24 02:43:53 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_signals;

void	cleanup_resources(t_token **token, t_cmd **cmd, char *input)
{
	ft_lstclear_token(token);
	ft_lstclear_cmd(cmd);
	free(input);
}

void	process_line(char *input, t_shell *shell)
{
	t_token	*token;

	token = NULL;
	shell->cmd = NULL;
	lexer(input, &token);
	parser(token, shell);
	expansion(shell);
	handle_heredoc(shell);
	execution(shell);
	cleanup_resources(&token, &shell->cmd, input);
}

void	run_interactive_shell(t_shell *shell)
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
			process_line(input, shell);
		}
	}
}

void	run_script_shell(t_shell *shell)
{
	char	*input;

	while (true)
	{
		input = get_next_line(STDIN_FILENO);
		if (!input)
			break ;
		process_line(input, shell);
	}
}

int	main(void)
{
	t_shell	shell;

	shell.env = init_env();
	shell.exit_status = 0;
	if (!shell.env)
		return (EXIT_FAILURE);
	else if (isatty(STDIN_FILENO))
		run_interactive_shell(&shell);
	else
		run_script_shell(&shell);
	ft_lstclear_env(&shell.env);
	return (EXIT_SUCCESS);
}
