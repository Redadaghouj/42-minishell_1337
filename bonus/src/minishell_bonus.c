/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:26:52 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/08/27 19:43:46 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_bonus.h"

void print_args(char **args)
{
    int i = 0;
    while (args && args[i])
    {
        printf("args[%d]: %s\n", i, args[i]);
        i++;
    }
    printf("args[%d]: NULL\n", i);
}

char  *return_type(unsigned int type)
{
	if (type == TOKEN_HEREDOC)
		return("<<");
	else if (type == TOKEN_APPEND_OUT)
		return(">>");
	else if (type == TOKEN_REDIR_IN)
		return("<");
	else if (type == TOKEN_REDIR_OUT)
		return(">");
	else
		return("NON");
}

void	print_redirs(t_redir *redir)
{
	int i = 0;
	while (redir)
	{
		printf("  redir[%d]: file='%s', type='%s'\n", i, redir->file_delim, return_type(redir->type));
		redir = redir->next;
		i++;
	}
	if (i == 0)
		printf("  no redirs\n");
}

void	print_cmd_list(t_cmd *cmd)
{
	int cmd_i = 0;
	while (cmd)
	{
		printf("cmd[%d]:\n", cmd_i);

		// Print args
		if (cmd->args)
		{
			for (int i = 0; cmd->args[i]; i++)
				printf("  args[%d]: %s\n", i, cmd->args[i]);
		}
		else
			printf("  no args\n");

		// Print redirs
		print_redirs(cmd->redir);

		cmd = cmd->next;
		cmd_i++;
	}
}

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
	handle_heredoc(shell);
	execution(shell);
	// print_cmd_list(shell->cmd);
	cleanup_resources(&shell->cmd, input);
}

void	run_interactive_shell(t_shell *shell)
{
	char	*input;

	setup_main_signals();
	while (true)
	{
		input = readline("☢️ shellnobyl$ ");
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
	shell.exit_status = 0;
	if (isatty(STDIN_FILENO))
		run_interactive_shell(&shell);
	else
		run_script_shell(&shell);
	ft_lstclear_env(&shell.env);
	return (shell.exit_status);
}
