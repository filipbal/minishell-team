/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghani <ghani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:15:12 by fbalakov          #+#    #+#             */
/*   Updated: 2025/03/02 10:47:53 by ghani            ###   ########.fr       */
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
# include <termios.h>

# define PROMPT "minishell$ "
# define MAX_TOKENS 64

typedef enum
{
	UNDEFINED,
	OPERATOR,
	COMMAND,
	VARIABLE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_type;

typedef struct s_shell
{
	char	*input;
	char	*tokens[MAX_TOKENS];
	t_type	token_type[MAX_TOKENS];
	int		exit_status;
	int		running;
}	t_shell;

/* Signal handling */
extern volatile sig_atomic_t g_signal_received;
void	signal_handler(int signo);
void	setup_signals(void);

void	init_shell(t_shell *shell);
void	cleanup_shell(t_shell *shell);
int		process_input(t_shell *shell);

void	tokenize(t_shell *shell);
void	find_tokens(char *ptr, int *i, int *start, int *length);
void	get_token_type(t_shell *shell);
void	get_token_type_2(t_shell *shell, int i);
void	check_tokens(t_shell *shell);

int		ft_strcmp(char *s1, char *s2);



const char *token_type_to_string(t_type type);

#endif