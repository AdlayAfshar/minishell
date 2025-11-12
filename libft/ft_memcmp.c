/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:35:16 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/02 20:35:18 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*sss1;
	const unsigned char	*sss2;

	i = 0;
	sss1 = (const unsigned char *)s1;
	sss2 = (const unsigned char *)s2;
	while ((sss1[i] != '\0' || sss2[i] != '\0') && i < n)
	{
		if (sss1[i] > sss2[i])
			return (1);
		if (sss1[i] < sss2[i])
			return (-1);
		i++;
	}
	return (0);
}

/*
#include <stdio.h>
#include <string.h>

int main(void)
{
    char str[] = "Hello";
    char str1[] = "Hell";

    printf("ft_memcmp1:   %d\n", ft_memcmp(str, "str", 3));
    printf("ft_memcmp1:   %d\n\n", ft_memcmp(str, "str", 3));
    printf("ft_memcmp2:   %d\n", ft_memcmp("str", "stR", 3));
    printf("memcmp2:      %d\n\n", memcmp("str", "stR", 3));
    printf("ft_memcmp3:   %d\n", ft_memcmp("str", "st", 3));
    printf("memcmp3:      %d\n\n", memcmp("str", "st", 3));
    printf("ft_memcmp4:   %d\n", ft_memcmp("str", "st", 1));
    printf("memcmp4:      %d\n\n", memcmp("str", "st", 1));
    printf("ft_memcmp5:   %d\n", ft_memcmp("str", "str", 5));
    printf("memcmp5:      %d\n\n", memcmp("str", "str", 5));
    printf("ft_memcmp6:   %d\n", ft_memcmp("", "str", 5));
    printf("memcmp6:      %d\n\n", memcmp("", "str", 5));
    printf("ft_memcmp7:   %d\n", ft_memcmp("str", "", 5));
    printf("memcmp7:      %d\n\n", memcmp("str", "", 5));
    printf("ft_memcmp8:   %d\n", ft_memcmp("", "str", 3));
    printf("memcmp8:      %d\n\n", memcmp("", "str", 3));
    printf("ft_memcmp9:   %d\n", ft_memcmp("str", "", 3));
    printf("memcmp9:      %d\n\n", memcmp("str", "", 3));
    printf("memcmp10:     %d\n", memcmp(str, "Hel", 3));
    printf("ft_memcmp10:  %d\n\n", ft_memcmp(str, "Hel", 3));
    printf("memcmp11:     %d\n", memcmp(str, str1, 5));
    printf("ft_memcmp11:  %d\n\n", ft_memcmp(str, str1, 5));
    printf("memcmp12:     %d\n", memcmp(str, str1, 6));
    printf("ft_memcmp12:  %d\n\n", ft_memcmp(str, str1, 6));
    printf("memcmp13:     %d\n", memcmp(str, str1, 3));
    printf("ft_memcmp13:  %d\n\n", ft_memcmp(str, str1, 3));
    printf("memcmp14:     %d\n", memcmp(str, str, 0));
    printf("ft_memcmp14:  %d\n", ft_memcmp(str, str, 0));
    return (0);
}
*/
