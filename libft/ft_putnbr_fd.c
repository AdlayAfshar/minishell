/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:26:52 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/02 20:27:30 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n == -2147483648)
		{
			ft_putchar_fd('2', fd);
			ft_putnbr_fd(147483648, fd);
			return ;
		}
		n = -n;
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd(n % 10 + 48, fd);
}

// void	ft_putnbr_fd(int n, int fd)
// {
// 	long	nb;

// 	nb = n;
// 	if (nb < 0)
// 	{
// 		write(fd, "-", 1);
// 		nb *= -1;
// 	}
// 	if (nb > 9)
// 	{
// 		ft_putnbr_fd(nb / 10, fd);
// 		ft_putchar_fd((nb % 10) + '0', fd);
// 	}
// 	else
// 		ft_putchar_fd(nb + '0', fd);
// }
