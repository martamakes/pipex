/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:32:41 by marta             #+#    #+#             */
/*   Updated: 2024/09/15 00:28:38 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_permission_error(char *filename)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd("permission denied: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd("\n", 2);
}

void	handle_infile_error(char *filename)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd("No such file or directory: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd("\n", 2);
}

void	handle_error(char *context, char *detail, int error_code)
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
	else
	{
		ft_putstr_fd(strerror(error_code), 2);
		ft_putstr_fd("\n", 2);
	}
	if (error_code == ENOENT && context && ft_strncmp(context, "execve",
			6) == 0)
		exit(127);
	else if (error_code == EACCES || error_code == ENOEXEC)
		exit(126);
	else
		exit(1);
}
