/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:18:07 by mvigara-          #+#    #+#             */
/*   Updated: 2024/02/21 13:10:42 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	aux;

	aux = n;
	if (aux < 0)
	{
		ft_putchar_fd('-', fd);
		aux *= -1;
	}
	if (aux > 9)
	{
		ft_putnbr_fd(aux / 10, fd);
		ft_putnbr_fd(aux % 10, fd);
	}
	else
		ft_putchar_fd(aux + '0', fd);
}
