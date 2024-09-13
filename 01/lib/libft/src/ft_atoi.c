/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:17:31 by mvigara-          #+#    #+#             */
/*   Updated: 2024/02/21 16:48:48 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Convert initial portion of string to integer.
 * This function converts the initial portion of the string
 * pointed to by str to int representation. It skips leading
 * whitespace characters and then parses the string until it
 * reaches a non-digit character. The base is assumed to be 10.
 * A minus sign can precede the digits to indicate a negative number.
 * @param str Pointer to null-terminated string to convert.
 * @return Converted integer value.
 */
int	ft_atoi(const char *str)
{
	int				neg;
	size_t			i;
	unsigned int	num;

	i = 0;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == ' ' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f')
		i++;
	neg = 1;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	num = 0;
	while (ft_isdigit(str[i]))
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}
