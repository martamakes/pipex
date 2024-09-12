/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:18:38 by mvigara           #+#    #+#             */
/*   Updated: 2024/03/02 16:13:48 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n == INT_MIN)
		return (11);
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		++count;
	}
	return (count);
}

static int	count_digits_unsigned(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		++count;
	}
	return (count);
}

int	printf_number(va_list val)
{
	int	nb;
	int	count;

	nb = va_arg(val, int);
	count = 0;
	ft_putnbr_fd(nb, 1);
	count += count_digits(nb);
	return (count);
}

int	printf_u(va_list val)
{
	int				nb;
	unsigned int	un;

	nb = va_arg(val, int);
	un = (unsigned int)nb;
	ft_putunbr_fd(un, 1);
	return (count_digits_unsigned(un));
}
