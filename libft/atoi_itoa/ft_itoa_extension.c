/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_extension.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:40:52 by minkim3           #+#    #+#             */
/*   Updated: 2023/04/30 20:52:07 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_numlen(long long n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n / 10 >= 1)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*ft_putnum(char *arr, long long n, int len)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		arr[0] = '-';
		n *= -1;
	}
	while (n / 10 >= 1)
	{
		arr[len - 1 - i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	arr[len - 1 - i] = n + '0';
	return (arr);
}

char	*ft_itoa_extension(long long n)
{
	char	*arr;
	int		len;

	len = ft_numlen(n);
	arr = (char *)malloc(sizeof(char) * (len + 1));
	if (!arr)
		return (NULL);
	arr = ft_putnum(arr, n, len);
	arr[len] = '\0';
	return (arr);
}
