/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:35:36 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/02 20:35:38 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

/*

#include <stdio.h>
#include <string.h>

int main(void)
{

    char str[50];
    char str1[50];
    char str2[50] = "hello, world!";

    printf("Before ft_memcpy(): %s\n", str2);

    memcpy(str, str2, sizeof(str1));
    ft_memcpy(str1, str2, sizeof(str1));

    printf("After    memcpy():  %s\n", str);
    printf("After ft_memcpy():  %s\n", str1);

    return (0);
}
*/
