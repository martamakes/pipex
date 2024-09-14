/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marta <marta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:55:24 by mvigara           #+#    #+#             */
/*   Updated: 2024/09/14 15:06:36 by marta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    child_process(char **argv, char **envp, int *pipe_fd)
{
    int     infile;
    char    *path;

    infile = open(argv[1], O_RDONLY);
    if (infile == -1)
    {
        handle_error(NULL, argv[1], errno);
        if (errno == EACCES)
            exit(126);
        infile = open("/dev/null", O_RDONLY);
        if (infile == -1)
            handle_error("Error opening /dev/null", NULL, errno);
    }
    if (dup2(infile, STDIN_FILENO) == -1 || dup2(pipe_fd[1], STDOUT_FILENO) == -1)
        handle_error("Dup2 failed", NULL, errno);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    close(infile);
    path = find_path(argv[2], envp);
    if (!path)
        handle_error(NULL, argv[2], ENOENT);
    execute_command(path, argv[2], envp);
}

void    parent_process(char **argv, char **envp, int *pipe_fd)
{
    int     outfile;
    char    *path;

    outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile == -1)
    {
        if (errno == EISDIR)
            handle_error(NULL, argv[4], EISDIR);
        else
            handle_error(NULL, argv[4], errno);
        if (errno == EACCES)
            exit(1);
    }
    if (dup2(pipe_fd[0], STDIN_FILENO) == -1 || dup2(outfile, STDOUT_FILENO) == -1)
        handle_error("Dup2 failed", NULL, errno);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    close(outfile);
    path = find_path(argv[3], envp);
    if (!path)
        handle_error(NULL, argv[3], ENOENT);
    execute_command(path, argv[3], envp);
}

void    execute_command(char *path, char *argv, char **envp)
{
    char    **cmd;

    cmd = ft_split(argv, ' ');
    if (!cmd)
        handle_error("Memory allocation failed", NULL, errno);
    if (execve(path, cmd, envp) == -1)
    {
        free_matrix(cmd);
        free(path);
        handle_error("execve", cmd[0], errno);
    }
}

void    setup_pipes_and_execute(char **argv, char **envp)
{
    int     pipe_fd[2];
    pid_t   pid1;
    pid_t   pid2;

    if (pipe(pipe_fd) == -1)
        handle_error("pipe", NULL, errno);
    pid1 = fork();
    if (pid1 == -1)
        handle_error("fork", NULL, errno);
    if (pid1 == 0)
        child_process(argv, envp, pipe_fd);
    pid2 = fork();
    if (pid2 == -1)
        handle_error("fork", NULL, errno);
    if (pid2 == 0)
        parent_process(argv, envp, pipe_fd);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

int main(int argc, char **argv, char **envp)
{
    if (argc != 5)
    {
        ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
        exit(1);
    }
    setup_pipes_and_execute(argv, envp);
    return (0);
}
