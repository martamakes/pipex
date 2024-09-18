/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:43:21 by marta             #+#    #+#             */
/*   Updated: 2024/09/15 00:18:20 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*remove_quotes(char *token)
{
	char	*new_token;
	int		i;
	int		j;
	char	quote;

	new_token = malloc(sizeof(char) * (ft_strlen(token) + 1));
	if (!new_token)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (token[i])
	{
		if (!quote && is_quote(token[i]))
			quote = token[i];
		else if (quote && token[i] == quote)
			quote = 0;
		else
			new_token[j++] = token[i];
		i++;
	}
	new_token[j] = '\0';
	free(token);
	return (new_token);
}

// char	**parse_command(char *cmd)
// {
// 	char	**result;
// 	size_t	count;
// 	char	*token;
// 	size_t	max_tokens;

// 	count = 0;
// 	max_tokens = 64;
// 	result = ft_calloc((max_tokens + 1), sizeof(char *));
// 	if (!result)
// 		return (NULL);
// 	token = extract_token(&cmd);
// 	while (token && count < max_tokens)
// 	{
// 		result[count] = remove_quotes(token);
// 		if (!result[count])
// 		{
// 			free_matrix(result);
// 			return (NULL);
// 		}
// 		count++;
// 		token = extract_token(&cmd);
// 	}
// 	if (count == 0)
// 	{
// 		result[0] = ft_strdup(cmd);
// 		if (!result[0])
// 		{
// 			free(result);
// 			return (NULL);
// 		}
// 		count++;
// 	}
// 	result[count] = NULL;
// 	return (result);
// }
static char	**handle_empty_command(char **result, char *cmd)
{
	result[0] = ft_strdup(cmd);
	if (!result[0])
	{
		free(result);
		return (NULL);
	}
	result[1] = NULL;
	return (result);
}

static char	**process_tokens(char **result, char *cmd, size_t max_tokens)
{
	size_t	count;
	char	*token;

	count = 0;
	token = extract_token(&cmd);
	while (token && count < max_tokens)
	{
		result[count] = remove_quotes(token);
		if (!result[count])
		{
			free_matrix(result);
			return (NULL);
		}
		count++;
		token = extract_token(&cmd);
	}
	if (count == 0)
		return (handle_empty_command(result, cmd));
	result[count] = NULL;
	return (result);
}

char	**parse_command(char *cmd)
{
	char	**result;
	size_t	max_tokens;

	max_tokens = 64;
	result = ft_calloc((max_tokens + 1), sizeof(char *));
	if (!result)
		return (NULL);
	return (process_tokens(result, cmd, max_tokens));
}
