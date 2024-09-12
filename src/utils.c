/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marta <marta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:14:37 by mvigara           #+#    #+#             */
/*   Updated: 2024/09/12 10:26:39 by marta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_error(void)
{
	perror("Error");
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

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
	}
	free_matrix(paths);
	return (NULL);
}

void	execute_pipex(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (!cmd)
		handle_error();
	path = find_path(cmd[0], envp);
	if (!path)
	{
		free_matrix(cmd);
		exit(127);
	}
	if (access(path, X_OK) == -1)
	{
		free_matrix(cmd);
		free(path);
		exit(126);
	}
	if (execve(path, cmd, envp) == -1)
	{
		free_matrix(cmd);
		free(path);
		handle_error();
	}
}
