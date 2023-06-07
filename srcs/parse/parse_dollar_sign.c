/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar_sign.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 20:06:32 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/07 20:13:03 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *parse_dollar_question_mark_and_pid_number(char *value)
{
	char	*new_value;

	new_value = value;
	if (ft_strcmp(new_value, "$?") != 0 && ft_strcmp(new_value, "$$") != 0)
		return (value);
	if (ft_strcmp(new_value, "$?") == 0)
	{
		free(value);
		new_value = ft_itoa(g_exit_code);
	}
	else if (ft_strcmp(new_value, "$$") == 0)
	{
		free(value);
		new_value = ft_itoa(getpid());
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
	value = parse_dollar_question_mark_and_pid_number(value);
	if (is_dollar_sign_in_token(value) == FALSE)
		return (tokens);
	replace_env_key_to_value(&value, env);
	tokens[index].value = value;
	value = remove_quotes(value);
	env_tokens = create_tokens_by_lexical_analysis(value);
	tokens->value = value;
	new_tokens = insert_env_tokens(tokens, index, env_tokens);
	return (new_tokens);
}
