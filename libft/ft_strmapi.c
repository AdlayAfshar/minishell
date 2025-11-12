/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:20:15 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/02 20:21:20 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	length;
	char			*res;

	if (!s)
		return (NULL);
	length = ft_strlen(s);
	res = malloc(length * sizeof(char) + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < length)
	{
		res[i] = (*f)(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}

// char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
// {
// 	unsigned int	i;
// 	unsigned int	len;
// 	char			*str;

// 	i = 0;
// 	str = (char *)malloc(ft_strlen(s) + 1);
// 	if (!s || !f)
// 		return (0);
// 	len = ft_strlen(s);
// 	if (!str)
// 		return (0);
// 	while (s[i])
// 	{
// 		str[i] = f(i, (char)s[i]);
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }
