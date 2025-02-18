/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghani <ghani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:15:12 by fbalakov          #+#    #+#             */
/*   Updated: 2025/02/16 22:26:35 by ghani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "minishell$ "
# define MAX_TOKENS 64

typedef struct s_shell
{
	char	*input;
	char	*tokens[MAX_TOKENS];
	int		exit_status;
	int		running;
}	t_shell;

void	init_shell(t_shell *shell);
void	cleanup_shell(t_shell *shell);
int		process_input(t_shell *shell);

void	tokenize(t_shell *shell);
void	find_tokens(char *ptr, int *i, int *start, int *length);

#endif