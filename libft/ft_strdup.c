/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:36:54 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/02 20:36:58 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	unsigned int	i;
	unsigned int	len;
	char			*dup;

	i = 0;
	len = 0;
	while (s1[len] != '\0')
		len++;
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (0);
	while (i <= len)
	{
		dup[i] = s1[i];
		i++;
	}
	return (dup);
}

/*
#include <stdio.h>
#include <string.h>

int main(void)
{
    char str2[50] = "hello, world!";

    printf("Before ft_strdup(): %s\n", str2);

    printf("After    strdup():  %s\n", strdup(str2));
    printf("After ft_strdup():  %s\n", ft_strdup(str2));

    return (0);
}
*/
