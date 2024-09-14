/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marta <marta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:32:41 by marta             #+#    #+#             */
/*   Updated: 2024/09/14 15:09:48 by marta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    handle_error(char *context, char *detail, int error_code)
{
    ft_putstr_fd("pipex: ", 2);
    if (context)
    {
        ft_putstr_fd(context, 2);
        ft_putstr_fd(": ", 2);
    }
    if (detail)
    {
        ft_putstr_fd(detail, 2);
        ft_putstr_fd(": ", 2);
    }
    ft_putstr_fd(strerror(error_code), 2);
    ft_putstr_fd("\n", 2);
    if (error_code == ENOENT && context && ft_strncmp(context, "execve", 6) == 0)
        exit(127);
    else if (error_code == EACCES || error_code == ENOEXEC)
        exit(126);
    else
        exit(1);
}
