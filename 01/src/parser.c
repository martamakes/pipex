/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marta <marta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:43:21 by marta             #+#    #+#             */
/*   Updated: 2024/09/14 18:48:43 by marta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include "pipex.h"

static int is_quote(char c)
{
    return (c == '\'' || c == '"');
}

static char *extract_token(char **str)
{
    char    *start;
    char    quote;
    int     len;
    int     escaped;

    while (**str && **str == ' ')
        (*str)++;
    if (!**str)
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
    len = *str - start;
    return (ft_substr(start, 0, len));
}

static char *remove_quotes(char *token)
{
    char    *new_token;
    int     i;
    int     j;
    char    quote;

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

char **parse_command(char *cmd)
{
    char    **result;
    int     count;
    char    *token;

    count = 0;
    result = malloc(sizeof(char *) * (ft_strlen(cmd) / 2 + 2));
    if (!result)
        return (NULL);
    while ((token = extract_token(&cmd)))
    {
        result[count] = remove_quotes(token);
        if (!result[count])
        {
            free_matrix(result);
            return (NULL);
        }
        count++;
    }
    result[count] = NULL;
    return (result);
}
