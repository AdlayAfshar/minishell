/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:40:14 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/02 20:40:15 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

/*
#include <stdio.h>
#include <ctype.h>

int main(void)
{
        char check = 'o';
        printf("check: %c\n", check);
        printf("ft_toupper0: %c\n", ft_toupper(check));
        printf("toupper0:    %c\n", toupper(check));
        printf("ft_toupper1: %c\n", ft_toupper('g'));
        printf("toupper1:    %c\n", toupper('g'));
        printf("ft_toupper2: %c\n", ft_toupper('G'));
        printf("toupper2:    %c\n", toupper('G'));
        printf("ft_toupper3: %c\n", ft_toupper(' '));
        printf("toupper3:    %c\n", toupper(' '));
        printf("ft_toupper4: %c\n", ft_toupper('!'));
        printf("toupper4:    %c\n", toupper('!'));
        printf("ft_toupper5: %c\n", ft_toupper('1'));
        printf("toupper5:    %c\n", toupper('1'));
        return (0);
}
*/
