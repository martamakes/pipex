/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marta <marta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:55:24 by mvigara           #+#    #+#             */
/*   Updated: 2024/09/12 10:24:17 by marta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char **argv, char **envp, int *pipe_fd)
{
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		handle_error();
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		handle_error();
	if (dup2(infile, STDIN_FILENO) == -1)
		handle_error();
	close(infile);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute_pipex(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int *pipe_fd)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		handle_error();
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		handle_error();
	if (dup2(outfile, STDOUT_FILENO) == -1)
		handle_error();
	close(outfile);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute_pipex(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (argc != 5)
	{
		ft_putstr_fd("Error: Bad arguments\n", 2);
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 1);
		exit(EXIT_FAILURE);
	}
	if (pipe(pipe_fd) == -1)
		handle_error();
	pid = fork();
	if (pid == -1)
		handle_error();
	if (pid == 0)
		child_process(argv, envp, pipe_fd);
	waitpid(pid, NULL, 0);
	parent_process(argv, envp, pipe_fd);
	return (0);
}
