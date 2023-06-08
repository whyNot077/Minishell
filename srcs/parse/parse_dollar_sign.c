/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar_sign.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 20:06:32 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/08 10:30:44 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static char *is_str_in_the_value(char *value)
// {
// 	int i = 0;
// 	int start = 0;
// 	char *tmp;
// 	char *head_char;
// 	char *tail_char;
// 	char *new_value;

// 	while (value[i])
// 	{
// 		if (value[i] == '$')
// 		{
// 			if ((size_t)i == ft_strlen(value) - 1)
// 			{
// 				new_value = ft_strdup(value);
// 				return (new_value);
// 			}
// 			start = i;
// 			i++;
// 			if (value[i] == '?' )
// 			{
// 				head_char = ft_substr(value, 0, start);
// 				tail_char = ft_substr(value, i + 1, ft_strlen(value) - i - 1);
// 				tmp = ft_itoa(g_exit_code);
// 				new_value = ft_strjoin(head_char, tmp);
// 				free(tmp);
// 				free(head_char);
// 				tmp = ft_strjoin(new_value, tail_char);
// 				free(new_value);
// 				free(tail_char);
// 				new_value = tmp;
// 				return (new_value);
// 			}
// 			else if (value[i] == '$')
// 			{
// 				head_char = ft_substr(value, 0, start);
// 				tail_char = ft_substr(value, i + 1, ft_strlen(value) - i - 1);
// 				tmp = ft_itoa(getpid());
// 				new_value = ft_strjoin(head_char, tmp);
// 				free(tmp);
// 				free(head_char);
// 				tmp = ft_strjoin(new_value, tail_char);
// 				free(new_value);
// 				free(tail_char);
// 				new_value = tmp;
// 				return (new_value);
// 			}
// 		}
// 		i++;
// 	}
// 	new_value = ft_strdup(value);
// 	return (new_value);
// }

// static char *parse_dollar_question_mark_and_pid_number(char *value)
// {
// 	char *new_value;

// 	new_value = is_str_in_the_value(value);
// 	while (ft_strcmp(new_value, value) != 0)
// 	{
// 		free(value);
// 		value = new_value;
// 		new_value = is_str_in_the_value(value);
// 	}
// 	free(value);
// 	return (new_value);
// }
// Helper function to replace substring from start to end with a string created from replacement_value.

// Helper function to replace substring from start to end with a string created from replacement_value.

static char	*replace_substr(char *value, int start, int end,
		int replacement_value)
{
	char	*head;
	char	*tail;
	char	*replace_str;
	char	*tmp;
	char	*new_value;

	head = ft_substr(value, 0, start);
	tail = ft_substr(value, end, ft_strlen(value) - end);
	replace_str = ft_itoa(replacement_value);
	tmp = ft_strjoin(head, replace_str);
	free(head);
	free(replace_str);
	new_value = ft_strjoin(tmp, tail);
	free(tmp);
	free(tail);
	return (new_value);
}

static char	*is_str_in_the_value(char *value)
{
	int		i;
	int		replacement_value;
	char	*new_value;

	i = 0;
	replacement_value = 0;
	while (value[i])
	{
		if (value[i] == '$')
		{
			i++;
			if (value[i] == '?')
			{
				if (value[i + 1] == '\0' || value[i + 1] == '$' || is_space(value[i + 1]))
					replacement_value = g_exit_code;
				else
					continue ;
			}
			else if (value[i] == '$')
			{
				if (value[i + 1] == '\0' || value[i + 1] == '$' || is_space(value[i + 1]))
					replacement_value = getpid();
				else
					continue ;
			}
			else
			{
				continue ;
			}
			new_value = replace_substr(value, i - 1, i + 1, replacement_value);
			free(value);
			return (new_value);
		}
		i++;
	}
	return (value);
}

static char	*parse_dollar_question_mark_and_pid_number(char *value)
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

	value = parse_dollar_question_mark_and_pid_number(tokens[index].value);
	tokens[index].value = value;
	if (is_dollar_sign_in_token(tokens[index].value) == FALSE)
		return (tokens);
	replace_env_key_to_value(&tokens[index].value, env);
	value = remove_quotes(tokens[index].value);
	tokens[index].value = value;
	env_tokens = create_tokens_by_lexical_analysis(value);
	new_tokens = insert_env_tokens(tokens, index, env_tokens);
	return (new_tokens);
}
