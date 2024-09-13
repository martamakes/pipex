/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 08:11:02 by mvigara           #+#    #+#             */
/*   Updated: 2024/05/19 23:35:49 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last;
	char		*token;
	int			i;

	if (str != NULL)
		last = str;
	if (last == NULL)
		return (NULL);
	token = last;
	i = 0;
	while (last[i] != '\0')
	{
		if (ft_strchr(delim, last[i]) != NULL)
		{
			last[i] = '\0';
			last = &last[i + 1];
			return (token);
		}
		i++;
	}
	last = NULL;
	return (token);
}
