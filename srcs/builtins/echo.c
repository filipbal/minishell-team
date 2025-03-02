/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbalakov <fbalakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:18:50 by fbalakov          #+#    #+#             */
/*   Updated: 2025/03/02 16:01:28 by fbalakov         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

/*
** is_n_flag: Checks if the given argument is a valid -n flag
** The -n flag can include multiple 'n's, like -nn or -nnn
** @param str: The string to check
** @return: 1 if it's a valid -n flag, 0 otherwise
*/
static int	is_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/*
** parse_echo_flags: Process all -n flags in the tokens
** @param tokens: Array of tokens to examine
** @param n_flag: Pointer to store flag state (0 or 1)
** @return: Index of the first non-flag argument
*/
static int	parse_echo_flags(char **tokens, int *n_flag)
{
	int	i;

	i = 1;
	*n_flag = 0;
	while (tokens[i] && is_n_flag(tokens[i]))
	{
		*n_flag = 1;
		i++;
	}
	return (i);
}

/*
** execute_echo: Output the arguments with proper formatting
** @param tokens: Array of tokens to output
** @param start_idx: Index to start printing from
** @param n_flag: Whether to suppress the trailing newline
** @return: Always returns 0 (success)
*/
static int	execute_echo(char **tokens, int start_idx, int n_flag)
{
	int	i;

	i = start_idx;
	while (tokens[i])
	{
		ft_putstr_fd(tokens[i], STDOUT_FILENO);
		if (tokens[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

/*
** ft_echo: Implements the 'echo' builtin command
** Outputs all arguments with spaces between them
** Supports the -n flag to suppress the trailing newline
** @param shell: The shell structure
** @return: Always returns 0 (success)
*/
int	ft_echo(t_shell *shell)
{
	int	n_flag;
	int	arg_start;

	arg_start = parse_echo_flags(shell->tokens, &n_flag);
	execute_echo(shell->tokens, arg_start, n_flag);
	shell->exit_status = 0;
	return (0);
}
