/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:34:45 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/06 20:21:03 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*ptr;

	if (n == 0)
		return (NULL);
	i = 0;
	ptr = (const unsigned char *)s;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return ((void *)ptr + i);
		i++;
	}
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>

int main(void)
{
    char str[] = "Tutorial.spoint";
    char ch = 'i';
    char *ret;
    char *ter;
    ret = memchr(str, ch, strlen(str));
    ter = ft_memchr(str, ch, strlen(str));
    printf("ret: %s\n", ret);
    printf("ter: %s\n", ter);
    return (0);
}
*/
