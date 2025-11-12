/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:33:35 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/02 20:33:36 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (!(c >= 0 && c <= 127))
		return (0);
	return (1);
}

/*
#include <stdio.h>
#include <ctype.h>

int main(void)
{
    printf("ft_isascii:\n");
    printf("%d\n", ft_isascii('b'));
    printf("%d\n", ft_isascii('B'));
    printf("%d\n", ft_isascii('6'));
    printf("%d\n", ft_isascii(6));
    printf("%d\n", ft_isascii(128));
    printf("%d\n", ft_isascii(-6));
    printf("%d\n", ft_isascii(655));
    printf("%d\n", ft_isascii('\n'));
    printf("\n");

    printf("isascii:\n");
    printf("%d\n", isascii('b'));
    printf("%d\n", isascii('B'));
    printf("%d\n", isascii('6'));
    printf("%d\n", isascii(6));
    printf("%d\n", isascii(128));
    printf("%d\n", isascii(-6));
    printf("%d\n", isascii(655));
    printf("%d\n", isascii('\n'));
    printf("\n");
    return (0);
}
*/
