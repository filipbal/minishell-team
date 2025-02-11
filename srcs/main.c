/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbalakov <fbalakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:15:53 by fbalakov          #+#    #+#             */
/*   Updated: 2025/02/07 12:54:24 by fbalakov         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

static void	init_shell(t_shell *shell)
{
	shell->input = NULL;
	shell->exit_status = 0;
	shell->running = 1;
}

static void	cleanup_shell(t_shell *shell)
{
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	rl_clear_history();
}

static int	process_input(t_shell *shell)
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

	init_shell(&shell);
	while (shell.running)
	{
		shell.input = readline(PROMPT);
		if (!process_input(&shell))
		{
			ft_putstr_fd("\nexit\n", STDERR_FILENO);
			break ;
		}
		free(shell.input);
		shell.input = NULL;
	}
	cleanup_shell(&shell);
	return (shell.exit_status);
}
