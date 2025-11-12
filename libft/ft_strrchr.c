/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:39:44 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/02 20:39:46 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	if ((char)c == '\0')
		return ((char *)(&s[i]));
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)(&s[i]));
		i--;
	}
	return (0);
}

/*
#include <stdio.h>
#include <string.h>

int main(void)
{

    printf("ft_strrchr1: %s\n", ft_strrchr("hello, world", 'w'));
    printf("strrchr1:    %s\n\n", strrchr("hello, world", 'w'));
    printf("ft_strrchr2: %s\n", ft_strrchr("hello, world", '3'));
    printf("strrchr2:    %s\n\n", strrchr("hello, world", '3'));
    printf("ft_strrchr3: %s\n", ft_strrchr("hello, world", 67));
    printf("strrchr3:    %s\n\n", strrchr("hello, world", 67));
    printf("ft_strrchr4: %s\n", ft_strrchr("hello, world", 'l'));
    printf("strrchr4:    %s\n\n", strrchr("hello, world", 'l'));
    printf("ft_strrchr5: %s\n", ft_strrchr("hello, world", ','));
    printf("strrchr5:    %s\n\n", strrchr("hello, world", ','));
    printf("ft_strrchr6: %s\n", ft_strrchr("hello, world", '!'));
    printf("strrchr6:    %s\n\n", strrchr("hello, world", '!'));
    printf("ft_strrchr7: %s\n", ft_strrchr("hello, world", '\0'));
    printf("strrchr7:    %s\n\n", strrchr("hello, world", '\0'));
    printf("ft_strrchr8: %s\n", ft_strrchr("hello, world", 'H'));
    printf("strrchr8:    %s\n\n", strrchr("hello, world", 'H'));
    printf("ft_strrchr9: %s\n", ft_strrchr("hello, world", 'h'));
    printf("strrchr9:    %s\n\n", strrchr("hello, world", 'h'));
    printf("ft_strrchr9: %s\n", ft_strrchr("hello, world", ' '));
    printf("strrchr9:    %s\n\n", strrchr("hello, world", ' '));
    return (0);
}
*/
