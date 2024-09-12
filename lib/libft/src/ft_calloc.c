/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 22:09:56 by mvigara-          #+#    #+#             */
/*   Updated: 2024/02/21 13:01:53 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Allocates enough space for count objects that are size bytes each
 * and returns a pointer to the allocated memory.
 * The memory is set to zero. If allocation fails, returns NULL.
 * @count - Number of elements to allocate.
 * size - Size of each element.
 * Returns:
 * Pointer to allocated memory, or NULL if allocation fails.
 */
void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count != 0 && size != 0 && SIZE_MAX / count < size)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
