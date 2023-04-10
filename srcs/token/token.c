/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:09:12 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/10 14:24:07 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token(const char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		error_exit("malloc failed");
	token->value = ft_strdup(value);
	return (token);
}

int	is_operator(char c)
{
	return (c == ' ' || c == '|' || c == '&' || c == '<' || c == '>');
}

int	is_space(char c)
{
	return (c == ' ');
}

void	type_of_token(t_token *tokens, int token_index)
{
	char	*value;

	value = tokens[token_index].value;
	if (ft_strncmp(value, "|", 1) == 0)
		tokens[token_index].type = PIPE;
	else if (ft_strncmp(value, ">", 1) == 0)
		tokens[token_index].type = REDIRECT_OUT;
	else if (ft_strncmp(value, "<", 1) == 0)
		tokens[token_index].type = REDIRECT_IN;
	else if (ft_strncmp(value, ">>", 2) == 0)
		tokens[token_index].type = REDIRECT_APPEND;
	else if (ft_strncmp(value, "<<", 2) == 0)
		tokens[token_index].type = HEREDOC;
	else if (ft_strncmp(value, "&&", 2) == 0)
		tokens[token_index].type = AND;
	else if (ft_strncmp(value, "||", 2) == 0)
		tokens[token_index].type = OR;
	else
		tokens[token_index].type = WORD;
}

void	free_tokens(t_token **tokens_ptr)
{
	t_token	*tokens;
	int		i;

	tokens = *tokens_ptr;
	if (tokens == NULL)
		return ;
	i = 0;
	while (tokens[i].value != NULL)
	{
		free(tokens[i].value);
		tokens[i].value = NULL;
		i++;
	}
	free(tokens);
	*tokens_ptr = NULL;
}
