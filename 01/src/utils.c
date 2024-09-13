/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:14:37 by mvigara           #+#    #+#             */
/*   Updated: 2024/09/13 23:17:51 by mvigara-         ###   ########.fr       */
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
			{
				ft_putstr_fd("no such file or directory: ", 2);
				ft_putstr_fd(argv[i], 2);
				ft_putstr_fd("\n", 2);
			}
			else
			{
				ft_putstr_fd("command not found: ", 2);
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
