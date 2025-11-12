/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:34:23 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/02 20:34:24 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (!(c >= 32 && c <= 126))
		return (0);
	return (1);
}

/*

#include <stdio.h>
#include <ctype.h>

int main(void)
{
    printf("ft_isprint:\n");
    printf("%d\n", ft_isprint('b'));
    printf("%d\n", ft_isprint('B'));
    printf("%d\n", ft_isprint('6'));
    printf("%d\n", ft_isprint(6));
    printf("%d\n", ft_isprint(32));
    printf("%d\n", ft_isprint(31));
    printf("126: %d\n", ft_isprint(126));
    printf("%d\n", ft_isprint(127));
    printf("\n");

    printf("isprint:\n");
    printf("%d\n", isprint('b'));
    printf("%d\n", isprint('B'));
    printf("%d\n", isprint('6'));
    printf("%d\n", isprint(6));
    printf("%d\n", isprint(32));
    printf("%d\n", isprint(31));
    printf("126: %d\n", isprint(126));
    printf("%d\n", isprint(127));
    printf("\n");
    return (0);
}
*/
