/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marta <marta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:55:24 by mvigara           #+#    #+#             */
/*   Updated: 2024/09/14 12:46:19 by marta            ###   ########.fr       */
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
        print_error(argv[1], errno);
        infile = open("/dev/null", O_RDONLY);
        if (infile == -1)
            handle_error();
    }
    if (dup2(infile, STDIN_FILENO) == -1 || dup2(pipe_fd[1], STDOUT_FILENO) == -1)
        handle_error();
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    close(infile);
    path = find_path(argv[2], envp);
    if (!path)
    {
        print_error(argv[2], ENOENT);
        exit(EXIT_FAILURE);
    }
    execute_command(path, argv[2], envp);
}

void    parent_process(char **argv, char **envp, int *pipe_fd)
{
    int     outfile;
    char    *path;

    outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile == -1)
    {
        print_error(argv[4], errno);
        outfile = open("/dev/null", O_WRONLY);
        if (outfile == -1)
            handle_error();
    }
    if (dup2(pipe_fd[0], STDIN_FILENO) == -1 || dup2(outfile, STDOUT_FILENO) == -1)
        handle_error();
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    close(outfile);
    path = find_path(argv[3], envp);
    if (!path)
    {
        print_error(argv[3], ENOENT);
        exit(EXIT_FAILURE);
    }
    execute_command(path, argv[3], envp);
}

void	execute_command(char *path, char *argv, char **envp)
{
	char	**cmd;

	cmd = ft_split(argv, ' ');
	if (!cmd)
		handle_error();
	if (execve(path, cmd, envp) == -1)
	{
		print_error(cmd[0], errno);
		free_matrix(cmd);
		free(path);
		exit(EXIT_FAILURE);
	}
}

void	setup_pipes_and_execute(char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipe_fd) == -1)
		handle_error();
	pid1 = fork();
	if (pid1 == -1)
		handle_error();
	if (pid1 == 0)
		child_process(argv, envp, pipe_fd);
	pid2 = fork();
	if (pid2 == -1)
		handle_error();
	if (pid2 == 0)
		parent_process(argv, envp, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		ft_putstr_fd("Error: Bad arguments\n", 2);
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		exit(EXIT_FAILURE);
	}
	check_empty_args(argc, argv);
	setup_pipes_and_execute(argv, envp);
	return (0);
}
