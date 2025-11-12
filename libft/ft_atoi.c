/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:31:35 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/02 20:31:39 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	sig;

	sig = 1;
	res = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\r'
		|| *str == '\f' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
		{
			sig = -sig;
		}
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		res = (res * 10) + (*str - 48);
		str++;
	}
	return (res * sig);
}

/*
#include <stdio.h>
// #include <stdlib.h>
// A simple main function to test ft_atoi
int main(void)
{
    char str1[] = " ---+--+1234ab567";
    char str2[] = "   +42";
    char str3[] = "   -123";
    char str4[] = "42";
    char str5[] = "   ---+--+2147483647";
    char str6[] = "   ---+--+-2147483648";

    printf("str1: %d\n", atoi(str1));
    printf("str1: %d\n\n", ft_atoi(str1)); // Expected output: -1234
    printf("str2: %d\n", atoi(str2));
    printf("str2: %d\n\n", ft_atoi(str2)); // Expected output: 42
    printf("str3: %d\n", atoi(str3));
    printf("str3: %d\n\n", ft_atoi(str3)); // Expected output: -123
    printf("str4: %d\n", atoi(str4));
    printf("str4: %d\n\n", ft_atoi(str4)); // Expected output: 42
    printf("str5: %d\n", atoi(str5));
    printf("str5: %d\n\n", ft_atoi(str5)); // Expected output: -2147483647
    printf("str6: %d\n", atoi(str6));
    printf("str6: %d\n", ft_atoi(str6)); // Expected output: 2147483648

    return 0;
}
*/
