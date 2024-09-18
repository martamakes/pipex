/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:58:04 by marta             #+#    #+#             */
/*   Updated: 2024/09/14 21:27:30 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*handle_absolute_path(char **args)
{
	if (ft_strchr(args[0], '/'))
		return (ft_strdup(args[0]));
	return (NULL);
}

char	*get_path_from_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	return (envp[i] + 5);
}

char	*search_in_path(char *cmd, char *env_path)
{
	char	**paths;
	char	*path;

	paths = ft_split(env_path, ':');
	if (!paths)
		return (NULL);
	path = find_executable(paths, cmd);
	free_matrix(paths);
	return (path);
}

char	*find_executable(char **paths, char *cmd)
{
	char	*path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		path = join_path(paths[i], cmd);
		if (!path)
			return (NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
	}
	return (NULL);
}

char	*join_path(char *dir, char *cmd)
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
