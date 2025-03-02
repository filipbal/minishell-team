/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbalakov <fbalakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:18:58 by fbalakov          #+#    #+#             */
/*   Updated: 2025/03/02 15:10:49 by fbalakov         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

/*
** ft_env: Implements the 'env' builtin
** Displays all environment variables
** @param shell: The shell structure
** @return: 0 on success, 1 on failure
*/
int	ft_env(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->tokens[1])
	{
		ft_putstr_fd("env: too many arguments\n", STDERR_FILENO);
		shell->exit_status = 1;
		return (1);
	}
	
	// We need to have the environment in the shell structure
	if (!shell->env)
	{
		ft_putstr_fd("env: environment not available\n", STDERR_FILENO);
		shell->exit_status = 1;
		return (1);
	}
	
	while (shell->env[i])
	{
		ft_putendl_fd(shell->env[i], STDOUT_FILENO);
		i++;
	}
	
	shell->exit_status = 0;
	return (0);
}