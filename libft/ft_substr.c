/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 19:45:27 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/04 18:44:07 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	src_len;
	char	*ptr;

	if (!s)
		return (NULL);
	src_len = ft_strlen(s);
	if (start >= src_len)
		return (ft_strdup(""));
	if (len > src_len - start)
		len = src_len - start;
	ptr = (char *)malloc(len + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	size_t	src_len;
// 	size_t	end_index;
// 	char	*ptr;

// 	src_len = 0;
// 	end_index = 0;
// 	end_index = start + len;
// 	while (s[src_len] != '\0')
// 		src_len++;
// 	ptr = (char *)malloc(len + 1);
// 	// if(!s)
// 	// 	return (NULL);
// 	if (start > src_len)
// 		return (0);
// 	if (len > src_len - start)
// 		len = src_len - start;
// 	src_len = 0;
// 	while (s[start] != '\0' && start < end_index)
// 	{
// 		ptr[src_len] = s[start];
// 		start++;
// 		src_len++;
// 	}
// 	ptr[src_len] = '\0';
// 	return (ptr);
// }

/*
#include <stdio.h>
int main(void)
{
    char str2[50] = "hello, world!";

    printf("Before ft_substr(): %s\n", str2);
    printf("After ft_substr():  %s\n", ft_substr(str2, 1, 8));
    return (0);
}
*/
