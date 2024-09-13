/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 22:06:37 by mvigara-          #+#    #+#             */
/*   Updated: 2024/02/21 13:11:07 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * ft_strdup - Duplicates a string
 * @s1: The string to duplicate
 * 
 * Allocates memory for a copy of the string s1, copies s1 
 * to the allocated memory, and returns a pointer to the copy.
 * The pointer points to a null-terminated string.
 *
 * Returns: Pointer to the copied string or NULL if insufficient memory.
*/
char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	len;

	len = ft_strlen(s1);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	ft_memcpy(ptr, s1, len);
	ptr[len] = '\0';
	return (ptr);
}
