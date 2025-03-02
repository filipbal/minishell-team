/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghani <ghani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:15:53 by fbalakov          #+#    #+#             */
/*   Updated: 2025/03/02 10:44:10 by ghani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell)
{
	int	i;

	shell->input = NULL;
	i = 0;
	while (i < MAX_TOKENS)
	{
		shell->tokens[i] = NULL;
		shell->token_type[i] = UNDEFINED;
		i++;
	}
	shell->exit_status = 0;
	shell->running = 1;
}

void	cleanup_shell(t_shell *shell)
{
	int	i;

	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	i = 0;
	while (shell->tokens[i])
		free(shell->tokens[i++]);
}

int	process_input(t_shell *shell)
{
	if (!shell->input)
	{
		shell->running = 0;
		return (0);
	}
	if (ft_strlen(shell->input) > 0)
		add_history(shell->input);
	if (!ft_strncmp(shell->input, "exit", 5))
		shell->running = 0;
	return (1);
}

int	main(void)
{
	t_shell		shell;

	setup_signals(); // Initialize signal handlers for proper Ctrl+C, Ctrl+D and Ctrl+\ behavior
	shell.running = 1;
	while (shell.running)
	{
		init_shell(&shell);
		shell.input = readline(PROMPT);
		if (!process_input(&shell))
		{
			ft_putstr_fd("\nexit\n", STDERR_FILENO);
			break ;
		}
		tokenize(&shell);
		get_token_type(&shell);
		check_tokens(&shell);
		// free(shell.input);
		// shell.input = NULL;
		// Next two lines are for testing purposes only
		for(int i = 0; shell.tokens[i]; i++)
			printf("%s : %s\n", shell.tokens[i], token_type_to_string(shell.token_type[i]));
		cleanup_shell(&shell);
	}
	rl_clear_history();
	return (shell.exit_status);
}

// THIS FUNCTIONS IS FOR TESTING PURPOSES ONLY
// The functions returns a string with the token type so it can be printed
const char *token_type_to_string(t_type type)
{
    switch (type)
    {
    case UNDEFINED:
        return "UNDEFINED";
    case OPERATOR:
        return "OPERATOR";
    case COMMAND:
        return "COMMAND";
    case VARIABLE:
        return "VARIABLE";
	case SINGLE_QUOTE:
        return "SINGLE_QUOTE";
	case DOUBLE_QUOTE:
        return "DOUBLE_QUOTE";
    default:
        return "UNKNOWN";
    }
}