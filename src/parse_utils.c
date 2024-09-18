/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 00:08:26 by mvigara-          #+#    #+#             */
/*   Updated: 2024/09/15 00:16:05 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

char	*skip_spaces(char **str)
{
	while (**str && **str == ' ')
		(*str)++;
	return (*str);
}

char	*extract_token(char **str)
{
	char	*start;
	char	quote;
	int		escaped;

	if (!skip_spaces(str) || !**str)
		return (NULL);
	start = *str;
	quote = 0;
	escaped = 0;
	while (**str && (quote || escaped || **str != ' '))
	{
		if (!escaped && is_quote(**str))
		{
			if (!quote)
				quote = **str;
			else if (quote == **str)
				quote = 0;
		}
		else if (!escaped && **str == '\\')
			escaped = 1;
		else
			escaped = 0;
		(*str)++;
	}
	return (ft_substr(start, 0, *str - start));
}
