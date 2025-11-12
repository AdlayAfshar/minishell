/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:36:13 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/04 17:50:45 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)b;
	while (i < len)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
/*
#include <stdio.h>
#include <string.h>

int main(void)
{
    //  memset(str + 13, '.', 8*sizeof(char));
    char str1[50] = "GeeksForGeeks is for programming geeks.";
    char str2[50] = "GeeksForGeeks is for programming geeks.";
    printf("Before memset() 1:\n %s\n", str1);
    printf("Before ft_memset() 2:\n %s\n", str2);

    // Fill 8 characters starting from str[13] with '.'
    memset(str1 + 13, '.', 8 * sizeof(char));
    ft_memset(str2 + 13, '.', 8 * sizeof(char));

    printf("After memset() 1:     %s\n", str1);
    printf("After ft_memset() 2:  %s\n", str2);

    return (0);
}
*/
