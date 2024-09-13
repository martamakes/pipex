/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 10:36:19 by mvigara           #+#    #+#             */
/*   Updated: 2024/05/19 23:59:15 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*change_base(unsigned long n, char *base)
{
	unsigned long	len;
	char			*buffer;
	int				i;
	char			*result;

	if (n == 0)
		return (ft_strdup("0"));
	len = ft_strlen(base);
	buffer = (char *)malloc(sizeof(char) * 21);
	if (buffer == NULL)
		return (NULL);
	i = 20;
	buffer[i] = '\0';
	while (n != 0)
	{
		buffer[--i] = base[n % len];
		n /= len;
	}
	result = ft_strdup(&buffer[i]);
	free(buffer);
	return (result);
}

int	printf_hex(va_list val)
{
	unsigned long	nb;
	int				i;
	char			*str;

	nb = va_arg(val, unsigned int);
	if (nb == 0)
		str = ft_strdup("0");
	else
		str = change_base(nb, "0123456789abcdef");
	ft_putstr_fd(str, 1);
	i = ft_strlen(str);
	free(str);
	return (i);
}

int	printf_upperhex(va_list val)
{
	unsigned int	nb;
	int				i;
	char			*str;

	nb = va_arg(val, unsigned int);
	str = change_base(nb, "0123456789ABCDEF");
	ft_putstr_fd(str, 1);
	i = ft_strlen(str);
	free(str);
	return (i);
}

int	printf_pointer(va_list val)
{
	void			*ptr;
	unsigned long	nb;
	int				i;
	char			*str;

	ptr = va_arg(val, void *);
	nb = (unsigned long)ptr;
	if (ptr == NULL)
	{
		ft_putstr_fd("(nil)", 1);
		return (ft_strlen("(nil)"));
	}
	else
		ft_putstr_fd("0x", 1);
	str = change_base(nb, "0123456789abcdef");
	ft_putstr_fd(str, 1);
	i = ft_strlen(str) + 2;
	free(str);
	return (i);
}
