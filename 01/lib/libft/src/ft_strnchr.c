/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:48:50 by mvigara           #+#    #+#             */
/*   Updated: 2024/02/21 16:47:16 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Searches for the first occurrence of a character in a string, up to a maximum
 *  length.
 *
 * @param s     The string to search in.
 * @param c     The character to search for.
 * @param max   The maximum length to search within.
 * @return      A pointer to the first occurrence of the character in the
 * string, or NULL if not found.
 */
char	*ft_strnchr(const char *s, int c, size_t max)
{
	size_t	i;

	i = 0;
	while (i < max && s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
