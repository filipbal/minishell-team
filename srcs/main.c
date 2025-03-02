/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbalakov <fbalakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:15:53 by fbalakov          #+#    #+#             */
/*   Updated: 2025/03/02 15:04:11 by fbalakov         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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

/*
** init_env: Initialize environment variables for the shell
** Makes a copy of the system environment
** @param shell: The shell structure
** @param env: The system environment
*/
void	init_env(t_shell *shell, char **env)
{
	int	i;
	int	env_count;

	env_count = 0;
	while (env[env_count])
		env_count++;
	
	shell->env = (char **)malloc(sizeof(char *) * (env_count + 1));
	if (!shell->env)
	{
		ft_putstr_fd("minishell: memory allocation error\n", STDERR_FILENO);
		exit(1);
	}
	
	i = 0;
	while (i < env_count)
	{
		shell->env[i] = ft_strdup(env[i]);
		if (!shell->env[i])
		{
			ft_putstr_fd("minishell: memory allocation error\n", STDERR_FILENO);
			// Free allocated memory before exiting
			while (--i >= 0)
				free(shell->env[i]);
			free(shell->env);
			exit(1);
		}
		i++;
	}
	shell->env[env_count] = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_shell		shell;

	(void)argc;
	(void)argv;
	setup_signals(); // Initialize signal handlers for proper Ctrl+C, Ctrl+D and Ctrl+\ behavior
	init_env(&shell, env);
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
		if (shell.tokens[0])
		{
			if (!ft_strncmp(shell.tokens[0], "pwd", 4))
				ft_pwd(&shell);
			else if (!ft_strncmp(shell.tokens[0], "env", 4))
				ft_env(&shell);
			// We'll add other builtins later
		}
		free(shell.input);
		shell.input = NULL;
		// Next two lines are for testing purposes only
		for(int i = 0; shell.tokens[i]; i++)
			printf("%s\n", shell.tokens[i]);
		cleanup_shell(&shell);
	}
	rl_clear_history();
	
	// Free environment before exiting
	if (shell.env)
	{
		int i = 0;
		while (shell.env[i])
			free(shell.env[i++]);
		free(shell.env);
	}
	
	return (shell.exit_status);
}