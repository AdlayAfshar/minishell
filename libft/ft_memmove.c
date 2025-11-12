/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:35:52 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/02 20:35:53 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	copy_bw(unsigned char *d, const unsigned char *s, size_t len)
{
	while (len > 0)
	{
		len--;
		d[len] = s[len];
	}
}

static void	copy_fw(unsigned char *d, const unsigned char *s, size_t len)
{
	while (len > 0)
	{
		*d = *s;
		d++;
		s++;
		len--;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (d > s)
		copy_bw(d, s, len);
	else
		copy_fw(d, s, len);
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
    printf("Before ft_memmove(): %s\n", str2);

    // Fill 8 characters starting from str[13] with '.'
    memmove(str, str2, sizeof(str));
    ft_memmove(str1, str2, sizeof(str1));

    printf("After memmove() 1:  %s\n", str);
    printf("After memmove() 2:  %s\n", str1);

    return (0);
}
*/
