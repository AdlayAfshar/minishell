/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:36:34 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/02 20:36:35 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (0);
}

/*

#include <stdio.h>
#include <string.h>

int main(void)
{
    printf("ft_strchr1: %s\n", ft_strchr("hello, world", 'w'));
    printf("strchr1:    %s\n", strchr("hello, world", 'w'));
    printf("ft_strchr2: %s\n", ft_strchr("hello, world", '3'));
    printf("strchr2:    %s\n", strchr("hello, world", '3'));
    printf("ft_strchr3: %s\n", ft_strchr("hello, world", 67));
    printf("strchr3:    %s\n", strchr("hello, world", 67));
    printf("ft_strchr4: %s\n", ft_strchr("hello, world", 'l'));
    printf("strchr4:    %s\n", strchr("hello, world", 'l'));
    printf("ft_strchr5: %s\n", ft_strchr("hello, world", ','));
    printf("strchr5:    %s\n", strchr("hello, world", ','));
    printf("ft_strchr6: %s\n", ft_strchr("hello, world", '!'));
    printf("strchr6:    %s\n", strchr("hello, world", '!'));
    printf("ft_strchr7: %s\n", ft_strchr("hello, world", '\0'));
    printf("strchr7:    %s\n", strchr("hello, world", '\0'));
    printf("ft_strchr8: %s\n", ft_strchr("hello, world", 'H'));
    printf("strchr8:    %s\n", strchr("hello, world", 'H'));
    printf("ft_strchr9: %s\n", ft_strchr("hello, world", 'h'));
    printf("strchr9:    %s\n", strchr("hello, world", 'h'));
    printf("ft_strchr10:%s\n", ft_strchr("hello, world", ' '));
    printf("strchr10:   %s\n", strchr("hello, world", ' '));
    return (0);
}

*/
