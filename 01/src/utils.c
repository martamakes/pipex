/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:14:37 by mvigara           #+#    #+#             */
/*   Updated: 2024/09/13 23:04:43 by mvigara-         ###   ########.fr       */
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
	char	*temp;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
		return (ft_strdup(cmd));
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
		{
			free_matrix(paths);
			return (NULL);
		}
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path, X_OK) == 0)
		{
			free_matrix(paths);
			return (path);
		}
		free(path);
	}
	free_matrix(paths);
	return (ft_strdup(cmd));
}

static char	*join_path_and_file(char *path, char *file)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, file);
	free(temp);
	return (full_path);
}

char	*get_outfile_path(char *outfile_arg)
{
	char	*full_path;
	char	*dir_path;
	char	*file_name;

	full_path = realpath(outfile_arg, NULL);
	if (full_path)
		return (full_path);
	dir_path = ft_strdup(outfile_arg);
	if (!dir_path)
		return (NULL);
	file_name = ft_strrchr(dir_path, '/');
	if (file_name)
		*file_name++ = '\0';
	else
	{
		free(dir_path);
		return (ft_strdup(outfile_arg));
	}
	full_path = realpath(dir_path, NULL);
	free(dir_path);
	if (full_path)
	{
		dir_path = join_path_and_file(full_path, file_name);
		free(full_path);
		return (dir_path);
	}
	return (ft_strdup(outfile_arg));
}
