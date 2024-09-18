/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:18:12 by mvigara-          #+#    #+#             */
/*   Updated: 2024/09/14 23:40:31 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_current_dir(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
			return (envp[i] + 4);
		i++;
	}
	return (NULL);
}

char	*get_file_path(char *file, char **envp)
{
	char	*cwd;
	char	*full_path;

	if (!file || file[0] == '\0')
		return (NULL);
	if (file[0] == '/')
		return (ft_strdup(file));
	cwd = get_current_dir(envp);
	if (!cwd)
		return (NULL);
	if (ft_strncmp(file, "./", 2) == 0)
		full_path = join_path(cwd, file + 2);
	else if (ft_strncmp(file, "../", 3) == 0)
		full_path = handle_parent_dir(cwd, file, envp);
	else
		full_path = join_path(cwd, file);
	return (full_path);
}

char	*handle_parent_dir(char *cwd, char *file, char **envp)
{
	char	*last_slash;

	last_slash = ft_strrchr(cwd, '/');
	if (last_slash)
		*last_slash = '\0';
	return (get_file_path(file + 3, envp));
}

char	*find_path(char *cmd, char **envp)
{
	char	**args;
	char	*path;
	char	*env_path;

	if (!cmd || !*cmd)
		return (NULL);
	args = ft_split(cmd, ' ');
	if (!args)
		return (NULL);
	path = handle_absolute_path(args);
	if (!path)
	{
		env_path = get_path_from_env(envp);
		if (env_path)
			path = search_in_path(args[0], env_path);
	}
	free_matrix(args);
	return (path);
}
