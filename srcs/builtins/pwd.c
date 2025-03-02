/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbalakov <fbalakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:19:23 by fbalakov          #+#    #+#             */
/*   Updated: 2025/03/02 14:41:25 by fbalakov         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

/*
** ft_pwd: Prints the current working directory
** @param shell: The shell structure
** @return: 0 on success, 1 on failure
*/
int	ft_pwd(t_shell *shell)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		shell->exit_status = 0;
		return (0);
	}
	else
	{
		ft_putstr_fd("minishell: pwd: ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		shell->exit_status = 1;
		return (1);
	}
}
