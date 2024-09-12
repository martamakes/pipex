/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 23:50:14 by mvigara           #+#    #+#             */
/*   Updated: 2024/05/19 23:36:53 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Checks if a character is a whitespace character.
 *
 * @param c The character to be checked.
 * @return 1 if the character is a whitespace character, 0 otherwise.
 */
int	ft_iswhitespace(char c)
{
	return (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\v'
		|| c == '\f');
}
