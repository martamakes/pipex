/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marta <marta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:18:12 by mvigara-          #+#    #+#             */
/*   Updated: 2024/09/14 08:35:02 by marta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "pipex.h"

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
*/
#include "pipex.h"

static char	*join_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, cmd);
	free(tmp);
	return (res);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (ft_strdup(cmd));
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		path = join_path(paths[i], cmd);
		if (!path || access(path, X_OK) == 0)
		{
			free_matrix(paths);
			return (path);
		}
		free(path);
	}
	free_matrix(paths);
	return (ft_strdup(cmd));
}

static char	*get_base_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
			return (envp[i] + 4);
		i++;
	}
	return ("/");
}

char	*get_file_path(char *file, char **envp)
{
	char	*base_path;
	char	*full_path;

	if (file[0] == '/')
		return (ft_strdup(file));
	base_path = get_base_path(envp);
	full_path = join_path(base_path, file);
	return (full_path);
}
