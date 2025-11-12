/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:32:54 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/02 20:32:56 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	int	is_digit;
	int	is_lower;
	int	is_upper;

	is_digit = (c >= '0' && c <= '9');
	is_lower = (c >= 'a' && c <= 'z');
	is_upper = (c >= 'A' && c <= 'Z');
	if (is_digit || is_lower || is_upper)
	{
		return (1);
	}
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>


int	main(void)
{
    printf("ft_isalnum:\n");
    printf("%d\n", ft_isalnum('b'));
    printf("%d\n", ft_isalnum('B'));
    printf("%d\n", ft_isalnum('6'));
    printf("%d\n", ft_isalnum(6));
    printf("%d\n", ft_isalnum('\n'));
    printf("\n");

    printf("isalnum:\n");
    printf("%d\n", isalnum('b'));
    printf("%d\n", isalnum('B'));
    printf("%d\n", isalnum('6'));
    printf("%d\n", isalnum(6));
    printf("%d\n", isalnum('\n'));
    printf("\n");
	
	return	(0);
}
*/
