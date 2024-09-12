/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:38:34 by mvigara           #+#    #+#             */
/*   Updated: 2024/02/21 13:16:44 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printf_char(va_list val)
{
	char	str;

	str = va_arg(val, int);
	ft_putchar_fd(str, 1);
	return (1);
}

int	printf_str(va_list val)
{
	char	*str;
	int		i;
	int		len;

	str = va_arg(val, char *);
	if (str == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar_fd(str[i], 1);
		i++;
	}
	len = ft_strlen(str);
	return (len);
}

int	printf_percent(va_list val __attribute__((unused)))
{
	ft_putchar_fd(37, 1);
	return (1);
}
