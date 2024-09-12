/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:05:18 by mvigara-          #+#    #+#             */
/*   Updated: 2024/08/12 12:06:29 by mvigara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (count);
}

static void	ft_free_tab(char **tab, size_t i)
{
	while (i > 0)
		free(tab[--i]);
	free(tab);
}

static int	ft_copy_words(char **tab, char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			j = 0;
			while (s[j] && s[j] != c)
				j++;
			tab[i] = ft_strndup(s, j);
			if (!tab[i])
			{
				ft_free_tab(tab, i);
				return (0);
			}
			i++;
			s += j;
		}
		else
			s++;
	}
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	size_t	words;

	if (!s || !*s)
	{
		tab = (char **)malloc(sizeof(char *));
		if (!tab)
			return (NULL);
		tab[0] = NULL;
		return (tab);
	}
	words = ft_count_words(s, c);
	tab = (char **)malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	if (!ft_copy_words(tab, s, c))
		return (NULL);
	tab[words] = NULL;
	return (tab);
}
