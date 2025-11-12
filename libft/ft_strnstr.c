/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:39:22 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/02 20:39:24 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (haystack[i + j] == needle[j] && i + j < len)
			{
				if (needle[j + 1] == '\0')
					return ((char *)haystack + i);
				j++;
			}
		}
		i++;
	}
	return (0);
}

/*

#include <stdio.h>
#include <string.h>

#define LIMIT 500

int main()
{
    char *haystack = "Eeny miny meeny miny moe!";
    char *needle = "miny";
    char *location;
    char *location2;

    printf("b: %s\n", haystack);
    location = strnstr(haystack, needle, LIMIT);
    location2 = ft_strnstr(haystack, needle, LIMIT);
    // location = strnstr(haystack, needle, sizeof(haystack));
    // location2 = ft_strnstr(haystack, needle, sizeof(haystack));
    // location = strnstr(haystack, needle, strlen(haystack));
    // location2 = ft_strnstr(haystack, needle, strlen(haystack));

    printf("strnstr:      %s\n", location);
    printf("ft_strnstr:   %s\n", location2);
    printf("b: %s\n", haystack);

    return (0);
}

*/
