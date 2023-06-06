/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar_sign.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 20:06:32 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/06 21:41:07 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	parse_dollar_question_mark(char *value)
{
	if (ft_strcmp(value, "$?") != 0)
		return ;
	free(value);
	value = ft_itoa(g_exit_code);
}

static t_token *make_new_tokens(size_t new_token_count)
{
	t_token	*new_tokens;

	new_tokens = (t_token *)malloc(sizeof(t_token) * new_token_count + 1);
	if (new_tokens == NULL)
	{
		perror("malloc");
		exit(1);
	}
	return (new_tokens);
}

t_token *	insert_env_tokens(t_token *tokens, size_t token_count, size_t index,
		t_token *env_tokens, size_t env_token_count)
{
	size_t		new_token_count;
	t_token	*new_tokens;
	size_t		i;
	size_t		j;

	new_token_count = token_count + env_token_count - 1;
	i = 0;
	j = 0;
	new_tokens = make_new_tokens(new_token_count);
	ft_memmove(new_tokens, tokens, sizeof(t_token) * index);
	ft_memmove(&new_tokens[index], env_tokens, sizeof(t_token) * env_token_count);
	ft_memmove(&new_tokens[index + env_token_count], &tokens[index + 1], sizeof(t_token) * (token_count - index - 1));
	// free_tokens(&tokens);
	// free_tokens(&env_tokens);
	free(env_tokens);
	new_tokens->token_count = new_token_count;
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

t_token	*	parse_dollar_sign(t_token *tokens, int index, char **env)
{
	char	*value;
	t_token	*env_tokens;

	value = tokens[index].value;
	parse_dollar_question_mark(value);
	if (is_dollar_sign_in_token(value) == FALSE)
		return (tokens);
	replace_env_key_to_value(&value, env);
	remove_quotes(value);
	env_tokens = create_tokens_by_lexical_analysis(value);
	tokens = insert_env_tokens(tokens, tokens->token_count, index, env_tokens, \
			env_tokens->token_count);
	return (tokens);
}
