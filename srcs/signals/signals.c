/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbalakov <fbalakov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:22:27 by fbalakov          #+#    #+#             */
/*   Updated: 2025/03/01 10:05:07 by fbalakov         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

/* Global variable to track received signals
 * Using sig_atomic_t ensures atomic access for signal safety
 */
volatile sig_atomic_t	g_signal_received = 0;

/* Signal handler function that processes incoming signals
 * Updates the global signal state and handles specific signals:
 * - SIGINT (Ctrl+C): Displays a new prompt on a new line
 * - SIGQUIT (Ctrl+\): No action needed (handled by SIG_IGN in setup)
 *
 * @param signo The signal number received
 */
void	signal_handler(int signo)
{
	g_signal_received = signo;
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/* Sets up signal handling for the shell
 * - Configures terminal settings to hide control character output
 * - Sets up SIGINT (Ctrl+C) to call our custom handler
 * - Sets up SIGQUIT (Ctrl+\) to be ignored
 */
void	setup_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	struct termios		term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	sa_int.sa_handler = signal_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
