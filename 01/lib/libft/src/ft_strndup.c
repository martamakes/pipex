/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:53:10 by mvigara-          #+#    #+#             */
/*   Updated: 2024/02/21 13:11:49 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_strndup - Duplicates n bytes of a string
 * @s1: The string to duplicate
 * @n: Number of bytes to copy
 *
 * Allocates memory for a copy of the string s1, copies at most n bytes
 * from s1 to the allocated memory, and returns a pointer to the copy.
 * The pointer points to a null-terminated string.
 *
 * Returns: Pointer to the copied string or NULL if insufficent memory
 */
char	*ft_strndup(const char *s1, size_t n)
{
	char	*ptr;

	ptr = (char *)malloc(sizeof(char) * (n + 1));
	if (ptr == NULL)
		return (NULL);
	ft_memcpy(ptr, s1, n);
	ptr[n] = '\0';
	return (ptr);
}
