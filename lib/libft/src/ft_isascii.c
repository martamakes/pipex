/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:21:44 by mvigara-          #+#    #+#             */
/*   Updated: 2024/01/26 10:15:04 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Checks if the given integer c falls within the ASCII character set
** (between 0 and 127 inclusive).
** @param c - The integer to check.
** @return 1 if c is an ASCII character, 0 otherwise.
*/
int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
