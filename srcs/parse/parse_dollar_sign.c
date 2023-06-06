/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar_sign.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 20:06:32 by minkim3           #+#    #+#             */
/*   Updated: 2023/06/06 20:09:47 by minkim3          ###   ########.fr       */
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

void	parse_dollar_sign(t_token *tokens, int index, char **env)
{
	char	*value;
	// t_token	*env_tokens;

	value = tokens[index].value;
	parse_dollar_question_mark(value);
	replace_env_key_to_value(&value, env);
	remove_quotes(value);
	// env_tokens = create_tokens_by_lexical_analysis(value);
	tokens[index].value = value;
}
