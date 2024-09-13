/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:21:37 by mvigara-          #+#    #+#             */
/*   Updated: 2024/02/21 13:11:28 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	const char	*src_ptr;
	char		*dst_ptr;

	if (dstsize == 0)
		return (ft_strlen(src));
	src_ptr = src;
	dst_ptr = dst;
	while (*src_ptr && ((size_t)(dst_ptr - dst)) < dstsize - 1)
	{
		*dst_ptr++ = *src_ptr++;
	}
	*dst_ptr = '\0';
	return (ft_strlen(src));
}
