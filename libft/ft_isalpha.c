/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:33:16 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/02 20:33:18 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	return (0);
}

/*
#include <stdio.h>
#include <ctype.h>

int main(void)
{
	printf("ft_isalpha:\n");
	printf("%d\n", ft_isalpha('b'));
	printf("%d\n", ft_isalpha('B'));
	printf("%d\n", ft_isalpha('6'));
	printf("%d\n", ft_isalpha(6));
	printf("%d\n", ft_isalpha('\n'));
	printf("\n");

	printf("isalpha:\n");
	printf("%d\n", isalpha('b'));
	printf("%d\n", isalpha('B'));
	printf("%d\n", isalpha('6'));
	printf("%d\n", isalpha(6));
	printf("%d\n", isalpha('\n'));
	printf("\n");

	return (0);
}
*/
