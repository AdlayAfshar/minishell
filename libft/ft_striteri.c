/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:22:53 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/02 20:22:58 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = -1;
	while (s[++i])
		f(i, &s[i]);
}

// void	ft_striteri(char *s, void (*f)(unsigned int, char *))
// {
// 	int	i;

// 	if (!s)
// 		return ;
// 	i = 0;
// 	while (s[i] != '\0')
// 	{
// 		(*f)(i, &s[i]);
// 		i++;
// 	}
// 	s[i] = '\0';
// }
