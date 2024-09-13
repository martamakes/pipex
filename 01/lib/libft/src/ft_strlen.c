/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:55:57 by mvigara-          #+#    #+#             */
/*   Updated: 2024/02/15 20:23:33 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Calculates the length of a null-terminated string.
 *
 * This function calculates the length of the string pointed to by `s`, 
 * excluding the terminating null character.
 *
 * @param s The string to calculate the length of.
 * @return The length of the string.
 */
size_t	ft_strlen(const char *s)
{
	size_t		i;

	i = 0;
	if (s)
		while (s[i])
			i++;
	return (i);
}
