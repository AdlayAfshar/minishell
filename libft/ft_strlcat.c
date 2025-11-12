/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:37:17 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/02 20:37:19 by yafshar          ###   ########.fr       */
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

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] != '\0' && i < dstsize)
		i++;
	while (src[j] != '\0' && (i + j + 1) < dstsize)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < dstsize)
		dst[i + j] = '\0';
	return (i + ft_strlen(src));
}

/*
#include <stdio.h>
#include <string.h>

int main(void)
{
	char s3[] = "Hello";
	char s2[] = "Bye";
	int size = 10;
	int result2;

	result2 = ft_strlcat(s3, s2, size);

	printf("Resulting string: '%s'\n", s3);
	printf("Return value:      %i\n", result2);

	char src[] = "Born to code";
	char dest[] = "1337 42";
	printf("%zu \n", ft_strlcat(dest, src, 20));
	printf("%s \n", dest);

	return 0;
}
*/
