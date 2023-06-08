/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar_sign.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 20:06:32 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/08 16:19:06 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*parse_dollar_question_mark(char *value)
{
	char	*new_value;

	new_value = is_str_in_the_value(value);
	while (new_value != value)
	{
		value = new_value;
		new_value = is_str_in_the_value(value);
	}
	return (new_value);
}

static t_token	*make_new_tokens(size_t new_token_count)
{
	t_token	*new_tokens;

	new_tokens = (t_token *)malloc(sizeof(t_token) * (new_token_count + 1));
	if (new_tokens == NULL)
	{
		perror("malloc");
		exit(1);
	}
	return (new_tokens);
}

t_token	*insert_env_tokens(t_token *tokens, size_t index, t_token *env_tokens)
{
	size_t	new_token_count;
	t_token	*new_tokens;
	size_t	token_count;
	size_t	env_token_count;

	token_count = tokens->token_count;
	env_token_count = env_tokens->token_count;
	new_token_count = token_count + env_token_count - 1;
	new_tokens = make_new_tokens(new_token_count);
	copy_tokens_to_new_tokens(new_tokens, tokens, env_tokens, index);
	new_tokens->token_count = new_token_count;
	free(tokens[index].value);
	free(env_tokens);
	free(tokens);
	return (new_tokens);
}

static int	is_dollar_sign_in_token(char *value)
{
	int	i;

	i = 0;
	while (value[i] != '\0')
	{
		if (value[i] == '$')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_token	*parse_dollar_sign(t_token *tokens, int index, char **env)
{
	char	*value;
	t_token	*env_tokens;
	t_token	*new_tokens;

	value = tokens[index].value;
	value = parse_dollar_question_mark(tokens[index].value);
	tokens[index].value = value;
	if (is_dollar_sign_in_token(tokens[index].value) == FALSE)
		return (tokens);
	(void)env;
	replace_env_key_to_value(&tokens[index].value, env);
	value = remove_quotes(tokens[index].value);
	tokens[index].value = value;
	env_tokens = create_tokens_by_lexical_analysis(value);
	new_tokens = insert_env_tokens(tokens, index, env_tokens);
	return (new_tokens);
}
