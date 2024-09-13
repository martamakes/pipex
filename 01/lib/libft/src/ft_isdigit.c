/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:54:15 by mvigara-          #+#    #+#             */
/*   Updated: 2024/02/21 11:15:02 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * ft_isdigit - Checks if a character is a digit (0-9)
 * @c: The character to check
 * Return: 1 if c is a digit, 0 otherwise
 */
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
