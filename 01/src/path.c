/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marta <marta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:18:12 by mvigara-          #+#    #+#             */
/*   Updated: 2024/09/14 12:53:05 by marta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

char    *find_path(char *cmd, char **envp)
{
    char    **paths;
    char    *path;
    char    *first_arg;
    int     i;

    if (!cmd || cmd[0] == '\0')
        return (NULL);
    first_arg = ft_split(cmd, ' ')[0];
    if (ft_strchr(first_arg, '/'))
        return (ft_strdup(first_arg));
    i = 0;
    while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
        i++;
    if (!envp[i])
        return (NULL);
    paths = ft_split(envp[i] + 5, ':');
    if (!paths)
        return (NULL);
    path = find_executable(paths, first_arg);
    free_matrix(paths);
    free(first_arg);
    return (path);
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
