/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marta <marta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:14:37 by mvigara           #+#    #+#             */
/*   Updated: 2024/09/12 16:47:01 by marta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void check_empty_args(int argc, char **argv)
{
    int i;

    i = 1;
    while (i < argc)
    {
        if (ft_strlen(argv[i]) == 0)
        {
            ft_putstr_fd("Error: Empty arguments are not allowed\n", 2);
            exit(1);
        }
        i++;
    }
}

void handle_error(void)
{
    perror("Error");
    exit(EXIT_FAILURE);
}

void free_matrix(char **matrix)
{
    int i;

    i = 0;
    while (matrix[i])
    {
        free(matrix[i]);
        i++;
    }
    free(matrix);
}

char *find_path(char *cmd, char **envp)
{
    char    **paths;
    char    *path;
    int     i;
    char    *part_path;

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

void execute_pipex(char *argv, char **envp)
{
    char **cmd;
    char *path;

    cmd = ft_split(argv, ' ');
    if (!cmd)
        handle_error();
    path = find_path(cmd[0], envp);
    if (!path)
    {
        ft_putstr_fd("Error: Command not found: ", 2);
        ft_putstr_fd(cmd[0], 2);
        ft_putstr_fd("\n", 2);
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
