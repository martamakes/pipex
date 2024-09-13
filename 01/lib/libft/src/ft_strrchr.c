/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:15:15 by mvigara-          #+#    #+#             */
/*   Updated: 2024/02/21 13:12:00 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*memrchr(const void *s, int c, size_t n)
{
	s = s + n - 1;
	while (n > 0)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((void *)s);
		s--;
		n--;
	}
	return (NULL);
}

char	*ft_strrchr(const char *s, int c)
{
	return (memrchr(s, c, ft_strlen(s) + 1));
}
