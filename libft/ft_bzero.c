/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:31:56 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/02 20:32:03 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n > 0)
	{
		*ptr = 0;
		ptr++;
		n--;
	}
}

/*

#include <stdio.h>
#include <string.h>

int main(void)
{
    char str1[50] = "GeeksForGeeks is for programming geeks.";
    char str2[50] = "GeeksForGeeks is for programming geeks.";
    printf("Before bzero() 1:\n %s\n", str1);
    printf("Before ft_bzero() 2:\n %s\n", str2);

    bzero(str1 + 13, 4 * sizeof(char));
    ft_bzero(str2 + 13, 8 * sizeof(char));

    printf("After bzero() 1:  %s\n", str1);
    printf("After bzero() 2:  %s\n", str2);

    return (0);
}
*/
