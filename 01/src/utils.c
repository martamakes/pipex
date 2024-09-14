/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marta <marta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:14:37 by mvigara           #+#    #+#             */
/*   Updated: 2024/09/14 12:38:08 by marta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_empty_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_strlen(argv[i]) == 0)
		{
			if (i == 1 || i == 4)
				print_error(argv[i], ENOENT);
			else
			{
				ft_putstr_fd("pipex: ", 2);
				ft_putstr_fd(strerror(ENOENT), 2);
				ft_putstr_fd(": ", 2);
				ft_putstr_fd(argv[i], 2);
				ft_putstr_fd("\n", 2);
			}
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	handle_error(void)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	print_error(char *arg, int error_code)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(error_code), 2);
	ft_putstr_fd("\n", 2);
}

int open_file(char *file, int flags)
{
    int     fd;
    char    *full_path;

    full_path = get_file_path(file, NULL);
    if (!full_path)
    {
        print_error(file, ENOENT);
        return (-1);
    }
    fd = open(full_path, flags, 0644);
    free(full_path);
    if (fd == -1)
        print_error(file, errno);
    return (fd);
}
