/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:26:52 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/08/28 18:23:27 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cleanup_resources(t_cmd **cmd, char *input)
{
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
	ft_lstclear_token(&token);
	expansion(shell);
	quote_cleaner(shell->cmd);
	if (handle_heredoc(shell))
	{
		cleanup_resources(&shell->cmd, input);
		return ;
	}
	execution(shell);
	cleanup_resources(&shell->cmd, input);
}

void	run_interactive_shell(t_shell *shell)
{
	char	*input;
	char	*prompt;

	prompt = NULL;
	setup_main_signals();
	while (true)
	{
		generate_prompt(&prompt);
		input = readline(prompt);
		free(prompt);
		if (is_eof_input(shell, input))
			break ;
		if (*input)
		{
			add_history(input);
			if (!ft_strncmp("exit", input, 4))
				printf("exit\n");
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
	shell.exit_status = EXIT_SUCCESS;
	if (isatty(STDIN_FILENO))
		run_interactive_shell(&shell);
	else
		run_script_shell(&shell);
	ft_lstclear_env(&shell.env);
	return (shell.exit_status);
}
