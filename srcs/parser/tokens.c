/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghani <ghani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:20:15 by fbalakov          #+#    #+#             */
/*   Updated: 2025/02/27 22:35:50 by ghani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Assigning token types to tokens
void	get_token_type(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->tokens[i])
	{
		if (ft_strcmp(shell->tokens[i], "|") == 0 ||
			ft_strcmp(shell->tokens[i], ">") == 0 ||
			ft_strcmp(shell->tokens[i], "<") == 0 ||
			ft_strcmp(shell->tokens[i], ">>") == 0 ||
			ft_strcmp(shell->tokens[i], "<<") == 0)
				shell->token_type[i] = OPERATOR;
		else if (ft_strcmp(shell->tokens[i], "cd") == 0 ||
			ft_strcmp(shell->tokens[i], "pwd") == 0 ||
			ft_strcmp(shell->tokens[i], "env") == 0 ||
			ft_strcmp(shell->tokens[i], "exit") == 0 ||
			ft_strcmp(shell->tokens[i], "echo") == 0 ||
			ft_strcmp(shell->tokens[i], "unset") == 0 ||
			ft_strcmp(shell->tokens[i], "export") == 0)
				shell->token_type[i] = COMMAND;
		else
			get_token_type_2(shell, i);
		i++;
	}
}

void	get_token_type_2(t_shell *shell, int i)
{
	// implement varuables $
	if (shell->tokens[i][0] == '\'' && ft_strlen(shell->tokens[i]) > 2 && 
		shell->tokens[i][strlen(shell->tokens[i] - 1)] == '\'')
			shell->token_type[i] = SINGLE_QUOTE;
	else if (shell->tokens[i][0] == '"' && ft_strlen(shell->tokens[i]) >= 2 && 
		shell->tokens[i][strlen(shell->tokens[i] - 1)] == '"')
			shell->token_type[i] = DOUBLE_QUOTE;
	else if (shell->tokens[i][0] == '$' && ft_strlen(shell->tokens[i]) >= 2)
		shell->token_type[i] = VARIABLE;
}

// Check if all tokens are valid, if not free and exit
void	check_tokens(t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->tokens[i])
	{
		//printf("%s : %s\n", shell->tokens[i], token_type_to_string(shell->token_type[i]));
		if (shell->token_type[i] == UNDEFINED)
		{
			cleanup_shell(shell);
			perror("Invalid input\n");
			exit (1);
		}
		i++;
	}

}

int ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}
