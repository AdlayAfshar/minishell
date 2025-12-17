

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 19:49:48 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/02 19:51:13 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	len_s1;
	unsigned int	len_s2;
	char			*join;

	i = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	join = (char *)malloc(len_s1 + len_s2 + 1);
	if (!join)
		return (0);
	while (i < len_s2 + len_s1)
	{
		if (i < len_s1)
			join[i] = s1[i];
		else
			join[i] = s2[i - len_s1];
		i++;
	}
	join[i] = '\0';
	return (join);
}

/*
#include <stdio.h>
#include <string.h>

int main(void)
{
    char s3[] = "Hello";
    char s2[] = "Bye";

    printf("Resulting string: '%s'\n", s3);
    printf("Return value: %s\n", ft_strjoin(s3, s2));

    return 0;
}
*/
