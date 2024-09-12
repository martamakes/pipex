/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:28:39 by mvigara-          #+#    #+#             */
/*   Updated: 2024/02/21 13:12:20 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*allocate_empty_string(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char));
	if (!str)
		return (NULL);
	*str = '\0';
	return (str);
}

char	*get_substring(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	char	*result;

	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	result = substr;
	while (len--)
		*substr++ = s[start++];
	*substr = '\0';
	return (result);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	strlen;

	if (!s || start >= ft_strlen(s))
		return (allocate_empty_string());
	if (len == 0)
		return (allocate_empty_string());
	strlen = ft_strlen(s + start);
	if (start >= ft_strlen(s))
		return (allocate_empty_string());
	if (len > strlen)
		len = strlen;
	substr = get_substring(s, start, len);
	return (substr);
}
