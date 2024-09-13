/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:26:15 by mvigara-          #+#    #+#             */
/*   Updated: 2024/02/21 11:14:55 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * ft_isalpha - Checks if the passed character is an alphabetic character.
 * @c: The character to check.
 * Return: 1 if character is alphabetic, 0 otherwise.
 */
int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
