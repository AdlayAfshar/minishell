/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:38:01 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/02 20:38:06 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	while (s[count] != '\0')
	{
		count += 1;
	}
	return (count);
}
/*
#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[] = "Hello, world!";

	printf("1: %lu\n", ft_strlen(str));
	printf("1: %lu\n", strlen(str));
	printf("2: %lu\n", ft_strlen("str"));
	printf("2: %lu\n", strlen("str"));
	printf("3: %lu\n", ft_strlen(" "));
	printf("3: %lu\n", strlen(" "));
	printf("4: %lu\n", ft_strlen(""));
	printf("4: %lu\n", strlen(""));
	printf("5: %lu\n", ft_strlen("\0"));
	printf("5: %lu\n", strlen("\0"));
	return (0);
}
*/
