/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:40:02 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/02 20:40:03 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

/*
#include <stdio.h>
#include <ctype.h>

int main(void)
{
    printf("ft_tolower1: %c\n", ft_tolower('g'));
    printf("tolower1:    %c\n", tolower('g'));
    printf("ft_tolower2: %c\n", ft_tolower('G'));
    printf("tolower2:    %c\n", tolower('G'));
    printf("ft_tolower3: %c\n", ft_tolower(' '));
    printf("tolower3:    %c\n", tolower(' '));
    printf("ft_tolower4: %c\n", ft_tolower('!'));
    printf("tolower4:    %c\n", tolower('!'));
    printf("ft_tolower5: %c\n", ft_tolower('1'));
    printf("tolower5:    %c\n", tolower('1'));

    return (0);
}
*/
