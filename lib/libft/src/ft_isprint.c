/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:59:55 by mvigara-          #+#    #+#             */
/*   Updated: 2024/01/26 13:54:50 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Checks if the given character is printable
** Returns 1 if the character code is between 32 and 126, 0 otherwise
*/
int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
