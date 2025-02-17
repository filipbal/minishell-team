/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghani <ghani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:15:53 by fbalakov          #+#    #+#             */
/*   Updated: 2025/02/17 20:13:13 by ghani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_shell *shell)
{
	int	i;

	shell->input = NULL;
	i = 0;
	while (i < MAX_TOKENS)
		shell->tokens[i++] = NULL;
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
		free(shell.input);
		shell.input = NULL;
		// Next two lines are for testing purposes only
		for(int i = 0; shell.tokens[i]; i++)
			printf("%s\n", shell.tokens[i]);
		cleanup_shell(&shell);
	}
	rl_clear_history();
	return (shell.exit_status);
}
