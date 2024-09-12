/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 22:32:17 by mvigara           #+#    #+#             */
/*   Updated: 2024/02/21 16:54:55 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	init_specifiers(t_format *sp)
{
	sp[0] = (t_format){'%', &printf_percent};
	sp[1] = (t_format){'s', &printf_str};
	sp[2] = (t_format){'c', &printf_char};
	sp[3] = (t_format){'d', &printf_number};
	sp[4] = (t_format){'i', &printf_number};
	sp[5] = (t_format){'u', &printf_u};
	sp[6] = (t_format){'x', &printf_hex};
	sp[7] = (t_format){'X', &printf_upperhex};
	sp[8] = (t_format){'p', &printf_pointer};
	sp[9] = (t_format){0, NULL};
}

static int	handle_specifier(const char **p, va_list args, t_format *sp)
{
	int	i;

	i = 0;
	while (sp[i].c != **p && sp[i].c != 0)
		i++;
	if (sp[i].c == **p)
		return (sp[i].f(args));
	else
		ft_putchar_fd(**p, 1);
	return (0);
}

static int	process_format(const char **p, va_list args, t_format *sp)
{
	int	len;

	len = 0;
	if (**p == '%')
	{
		(*p)++;
		len += handle_specifier(p, args, sp);
	}
	else
	{
		ft_putchar_fd(**p, 1);
		len++;
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int			len;
	va_list		args;
	t_format	sp[10];
	const char	*p;

	len = 0;
	va_start(args, format);
	init_specifiers(sp);
	p = format;
	while (*p)
	{
		len += process_format(&p, args, sp);
		p++;
	}
	va_end(args);
	return (len);
}
