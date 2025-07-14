/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:26:52 by mdaghouj          #+#    #+#             */
/*   Updated: 2025/07/14 02:04:04 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	free_things(t_token **token, t_cmd **cmd, char *input)
{
	ft_lstclear_token(token);
	ft_lstclear_cmd(cmd);
	free(input);
}

void	parsing(char *input, t_token **token, t_cmd **cmd, t_env *env)
{
	lexer(input, token);
	parser(*token, cmd);
	expansion(env, *cmd);
}

int	main(void)
{
	char	*input;
	t_token	*token;
	t_env	*env;
	t_cmd	*cmd;

	if (setup_lists(&token, &env, &cmd))
		return (EXIT_FAILURE);
	setup_signals();
	while (true)
	{
		input = readline("☢️ shellnobyl$ ");
		if (ends_prompt_loop(input))
			break ;
		if (*input)
			add_history(input);
		parsing(input, &token, &cmd, env);
		if (!handle_heredoc(cmd, env))
			print_cmd_list(cmd);
		free_things(&token, &cmd, input);
	}
	ft_lstclear_env(&env);
	return (EXIT_SUCCESS);
}
