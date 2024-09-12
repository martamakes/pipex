/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:16:07 by mvigara-          #+#    #+#             */
/*   Updated: 2024/02/21 14:26:04 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Searches for the first occurrence of a byte in a block of memory.
 * @param s     Pointer to the block of memory to search.
 * @param c     Byte to be located.
 * @param n     Number of bytes to be searched.
 * @return      Pointer to the first occurrence of the byte in the block of 
 * memory, or NULL if the byte is not found.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n > 0)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((void *)s);
		s++;
		n--;
	}
	return (NULL);
}
