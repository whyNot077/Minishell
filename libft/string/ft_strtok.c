/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim3 <minkim3@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:23:35 by minkim3           #+#    #+#             */
/*   Updated: 2023/03/20 15:32:55 by minkim3          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strtok(char **str, const char *sep)
{
	char	*start;
	char	*ptr;

	if (!str || !*str || !sep)
		return (NULL);
	start = *str;
	ptr = *str;
	while (*ptr)
	{
		if (ft_strchr(sep, *ptr))
		{
			*ptr = '\0';
			*str = ptr + 1;
			return (start);
		}
		ptr++;
	}
	*str = NULL;
	return (start);
}
