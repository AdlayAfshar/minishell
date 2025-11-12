/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafshar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:32:21 by yafshar           #+#    #+#             */
/*   Updated: 2025/01/02 20:32:31 by yafshar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*ptr;

	i = 0;
	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	ptr = malloc(count * size);
	if (ptr)
	{
		while (i < count * size)
		{
			((unsigned char *)ptr)[i] = 0;
			i++;
		}
	}
	return (ptr);
}

/*
#include <stdio.h>
#include <string.h>
int main(void)
{
    size_t count = 5;
    size_t size = sizeof(int);
    int *array;

    array = (int *)ft_calloc(count, size);
    if (array == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Check if the allocated memory is zero-initialized
    int all_zero = 1;
    for (size_t i = 0; i < count; i++)
    {
        if (array[i] != 0)
        {
            all_zero = 0;
            break;
        }
    }

    if (all_zero)
    {
        printf("ft_calloc works correctly: all el are zero-initialized.\n");
    }
    else
    {
        printf("ft_calloc failed: not all elements are zero-initialized.\n");
    }

    // Free the allocated memory
    free(array);

    return 0;
}

*/
