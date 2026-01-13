/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <yafshar@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:17:58 by yafshar           #+#    #+#             */
/*   Updated: 2026/01/13 17:43:50 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_len(long nb)
{
	int	len;

	len = 0;
	if (nb <= 0)
		len++;
	while (nb != 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		len;
	char	*str;

	nb = (long)n;
	len = nb_len(nb);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		str[--len] = '0' + (nb % 10);
		nb /= 10;
	}
	return (str);
}

// static int	nbnb(long nb)
// {
// 	int	len;

// 	len = 0;
// 	if (nb <= 0)
// 		len++;
// 	while (nb != 0)
// 	{
// 		nb = nb / 10;
// 		len++;
// 	}
// 	return (len);
// }

// char	*ft_itoa(int n)
// {
// 	long	nb;
// 	int		i;
// 	char	*str;

// 	nb = (long)n;
// 	i = nbnb(nb);
// 	str = malloc(sizeof(char) * (i + 1));
// 	if (!str)
// 		return (NULL);
// 	str[i] = '\0';
// 	if (n == 0)
// 	{
// 		str[0] = '0';
// 		return (str);
// 	}
// 	if (n < 0)
// 		str[0] = '-';
// 	while (n != 0)
// 	{
// 		if (str[0] == '-')
// 			str[i--] = '0' + -(n % 10);
// 		else
// 			str[i--] = '0' + (n % 10);
// 		n = n / 10;
// 	}
// 	return (str);
// }