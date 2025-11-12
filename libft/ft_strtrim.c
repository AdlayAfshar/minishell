/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 19:54:00 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/02 20:00:05 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	while (s[count] != '\0')
	{
		count += 1;
	}
	return (count);
}

static int	ft_chack(char c, char const *set)
{
	unsigned int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*trim;

	i = 0;
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_chack(s1[start], set))
		start++;
	while (end > start && ft_chack(s1[end - 1], set))
		end--;
	trim = (char *)malloc(sizeof(*s1) * (end - start + 1));
	if (!trim)
		return (NULL);
	while (start < end)
		trim[i++] = s1[start++];
	trim[i] = 0;
	return (trim);
}

/*
#include <stdio.h>
#include <string.h>

int main()
{
    char str1[50] = "xygeeksForGeeks is for programming geeks  xyxy";
    char str3[50] = "xy";

    printf("first  :  %s\n", str1);
    printf("second :  %s\n", str3);
    printf("After  :  %s\n", ft_strtrim(str1, str3));

    return (0);
}
*/
