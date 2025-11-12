/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:38:53 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/02 20:38:55 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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

    printf("ft_strncmp1:   %d\n", ft_strncmp(str, "str", 3));
    printf("ft_strncmp1:   %d\n\n", ft_strncmp(str, "str", 3));
    printf("ft_strncmp2:   %d\n", ft_strncmp("str", "stR", 3));
    printf("strncmp2:      %d\n\n", strncmp("str", "stR", 3));
    printf("ft_strncmp3:   %d\n", ft_strncmp("str", "st", 3));
    printf("strncmp3:      %d\n\n", strncmp("str", "st", 3));
    printf("ft_strncmp4:   %d\n", ft_strncmp("str", "st", 1));
    printf("strncmp4:      %d\n\n", strncmp("str", "st", 1));
    printf("ft_strncmp5:   %d\n", ft_strncmp("str", "str", 5));
    printf("strncmp5:      %d\n\n", strncmp("str", "str", 5));
    printf("ft_strncmp6:   %d\n", ft_strncmp("", "str", 5));
    printf("strncmp6:      %d\n\n", strncmp("", "str", 5));
    printf("ft_strncmp7:   %d\n", ft_strncmp("str", "", 5));
    printf("strncmp7:      %d\n\n", strncmp("str", "", 5));
    printf("ft_strncmp8:   %d\n", ft_strncmp("", "str", 3));
    printf("strncmp8:      %d\n\n", strncmp("", "str", 3));
    printf("ft_strncmp9:   %d\n", ft_strncmp("str", "", 3));
    printf("strncmp9:      %d\n\n", strncmp("str", "", 3));
    printf("strncmp10:     %d\n", strncmp(str, "Hel", 3));
    printf("ft_strncmp10:  %d\n\n", ft_strncmp(str, "Hel", 3));
    printf("strncmp11:     %d\n", strncmp(str, str1, 5));
    printf("ft_strncmp11:  %d\n\n", ft_strncmp(str, str1, 5));
    printf("strncmp12:     %d\n", strncmp(str, str1, 6));
    printf("ft_strncmp12:  %d\n\n", ft_strncmp(str, str1, 6));
    printf("strncmp13:     %d\n", strncmp(str, str1, 3));
    printf("ft_strncmp13:  %d\n\n", ft_strncmp(str, str1, 3));
    printf("strncmp14:     %d\n", strncmp(str, str, 0));
    printf("ft_strncmp14:  %d\n", ft_strncmp(str, str, 0));
    return (0);
}
*/
