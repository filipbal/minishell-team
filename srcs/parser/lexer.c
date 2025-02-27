/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghani <ghani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 15:19:50 by fbalakov          #+#    #+#             */
/*   Updated: 2025/02/27 21:45:55 by ghani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize(t_shell *shell)
{
	int		token_index;
	int		length;
	int		i;
	int		start;
	char	*ptr;

	token_index = 0;
	i = 0;
	ptr = shell->input;
	while (ptr[i] != '\0')
	{
		find_tokens(ptr, &i, &start, &length);
		if (length > 0)
		{
			shell->tokens[token_index] = (char *)malloc(length + 1);
			if (!shell->tokens[token_index])
			{
				perror("Failed to allocate memory\n");
				exit(1);
			}
			ft_strlcpy(shell->tokens[token_index], ptr + start, length + 1);
			token_index++;
		}
	}
	shell->tokens[token_index] = NULL;
}

void	find_tokens(char *ptr, int *i, int *start, int *length)
{
	char	quote;

	while (ptr[*i] == ' ' || ptr[*i] == '\t' || ptr[*i] == '\n')
		(*i)++;
	if (ptr[*i] == '\0')
		return ;
	if (ptr[*i] == '"' || ptr[*i] == '\'')
	{
		quote = ptr[*i];
		*start = *i;
		(*i)++;
		while (ptr[*i] != '\0' && ptr[*i] != quote)
			(*i)++;
		if (ptr[*i] == quote)
			(*i)++;
		*length = *i - *start;
	}
	else
	{
		*start = *i;
		while (ptr[*i] != '\0' && ptr[*i] != ' ' && ptr[*i] != '\t' && ptr[*i] != '\n')
			(*i)++;
		*length = *i - *start;
	}
}
