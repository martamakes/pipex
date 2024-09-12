/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:06:34 by mvigara-          #+#    #+#             */
/*   Updated: 2024/02/21 13:11:21 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dsize;

	dsize = 0;
	while (dest[dsize] != '\0' && dsize < dstsize)
		dsize++;
	i = dsize;
	while (src[dsize - i] != '\0' && dsize + 1 < dstsize)
	{
		dest[dsize] = src[dsize - i];
		dsize++;
	}
	if (i < dstsize)
		dest[dsize] = '\0';
	return (i + ft_strlen(src));
}
