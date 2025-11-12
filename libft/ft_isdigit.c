/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:34:05 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/02 20:34:08 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>


int	main(void)
{
    printf("ft_isdigit:\n");
    printf("b is %d\n", ft_isdigit('b'));
    printf("B is %d\n", ft_isdigit('B'));
    printf("6 is %d\n", ft_isdigit('6'));
    printf("(6) is %d\n", ft_isdigit(6));
    printf("line is %d\n", ft_isdigit('\n'));
    printf("\n");

    printf("isdigit:\n");
    printf("%d\n", isdigit('b'));
    printf("%d\n", isdigit('B'));
    printf("%d\n", isdigit('6'));
    printf("%d\n", isdigit(6));
    printf("%d\n", isdigit('\n'));
    printf("\n");

	return	(0);
}
*/
