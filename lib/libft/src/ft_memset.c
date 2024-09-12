/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:30:33 by mvigara-          #+#    #+#             */
/*   Updated: 2024/02/21 11:18:55 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Fills a block of memory with a specified value.
 * This function fills the first 'len' bytes of the memory block pointed to by
 * 'b' with the value specified by 'c'.
 * @param b     Pointer to the memory block to be filled.
 * @param c     Value to be set. It is passed as an int, but it is converted
 * to an unsigned char before being written.
 * @param len   Number of bytes to be filled.
 * @return      Pointer to the memory block 'b'.
 */
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;

	p = (unsigned char *)b;
	while (len--)
		*p++ = (unsigned char)c;
	return (b);
}
