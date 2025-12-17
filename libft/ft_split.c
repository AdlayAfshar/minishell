/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <yafshar@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:02:43 by yafshar           #+#    #+#             */
/*   Updated: 2025/12/17 20:28:21 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countword(char const *s, char c)
{
	size_t	count;
	int		i;

	i = 0;
	count = 0;
	if (!*s)
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	lenght;
	char	*ptr;

	i = 0;
	lenght = start + len;
	while (s[i] != '\0')
		i++;
	ptr = (char *)malloc(len + 1);
	if (start > i)
		return (0);
	if (len > i - start)
		len = i - start;
	i = 0;
	while (s[start] != '\0' && start < lenght)
	{
		ptr[i] = s[start];
		start++;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**lst;
	size_t	word_len;
	int		i;

	lst = (char **)malloc((ft_countword(s, c) + 1) * sizeof(char *));
	if (!s || !lst)
		return (0);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!ft_strchr(s, c))
				word_len = ft_strlen(s);
			else
				word_len = ft_strchr(s, c) - s;
			lst[i++] = ft_substr(s, 0, word_len);
			s += word_len;
		}
	}
	lst[i] = NULL;
	return (lst);
}

//#include <stdio.h>
//#include <string.h>
//
//int main()
//{
//    char str1[50] = "xygeeks,,,ForGeeks,geeks, xyxy";
//
//    printf("first  :  %s\n", str1);
//    // printf("After  :  %p\n", ft_split(str1, ',')[1]);
//    char **result = ft_split(str1, ',');
//    for (int i = 0; result[i]; i++)
//        printf("result[%d] = '%s'\n", i, result[i]);
//
//    for (int i = 0; result[i]; i++)
//        free(result[i]);
//    free(result);
//
//    return (0);
//}
