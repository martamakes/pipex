/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marta <marta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:14:37 by mvigara           #+#    #+#             */
/*   Updated: 2024/09/14 18:47:23 by marta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	open_file(char *file, int flags)
{
	int		fd;
	char	*full_path;

	full_path = get_file_path(file, NULL);
	if (!full_path)
	{
		handle_error(NULL, file, ENOENT);
		return (-1);
	}
	fd = open(full_path, flags, 0644);
	free(full_path);
	if (fd == -1)
		handle_error(NULL, file, errno);
	return (fd);
}
