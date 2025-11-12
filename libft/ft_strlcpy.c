/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:37:40 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/02 20:37:41 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	if (dstsize != 0)
	{
		while (src[i] != '\0' && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}

/*
#include <stdio.h>
#include <string.h>

int main()
{
	char src[] = "Hello, world!";
	char dst[50];
	char dst2[6];
	char dst3[1];
	size_t result;

	result = strlcpy(dst, src, sizeof(dst));
	printf("Test 1: Result = %zu, dst = \"%s\"\n", result, dst);

	result = strlcpy(dst2, src, sizeof(dst2));
	printf("Test 2: Result = %zu, dst2 = \"%s\"\n", result, dst2);

	result = strlcpy(dst3, src, 0);
	printf("Test 3: Result = %zu, dst3 = \"%s\"\n", result, dst3);

	result = ft_strlcpy(dst, src, sizeof(dst));
	printf("Test 1: Result = %zu, dst = \"%s\"\n", result, dst);

	result = ft_strlcpy(dst2, src, sizeof(dst2));
	printf("Test 2: Result = %zu, dst2 = \"%s\"\n", result, dst2);

	result = ft_strlcpy(dst3, src, 0);
	printf("Test 3: Result = %zu, dst3 = \"%s\"\n", result, dst3);

	result = strlcpy(dst3, src, 0);
	printf("Test 3 (Standard): Result = %zu, dst3 = \"%s\"\n", result, dst3);

	result = ft_strlcpy(dst3, src, 0);
	printf("Test 3 (Standard): Result = %zu, dst3 = \"%s\"\n", result, dst3);
	
	char empty_src[] = "";
	result = strlcpy(dst, empty_src, sizeof(dst));
	printf("Test 4: Result = %zu, dst = \"%s\"\n", result, dst);

	result = ft_strlcpy(dst, empty_src, sizeof(dst));
	printf("Test 4: Result = %zu, dst = \"%s\"\n", result, dst);

	result = strlcpy(dst, empty_src, sizeof(dst));
	printf("Test 4 (Standard): Result = %zu, dst = \"%s\"\n", result, dst);

	result = ft_strlcpy(dst, empty_src, sizeof(dst));
	printf("Test 4 (Standard): Result = %zu, dst = \"%s\"\n", result, dst);

	return 0;
}
*/
