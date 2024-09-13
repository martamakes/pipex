/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:55:24 by mvigara           #+#    #+#             */
/*   Updated: 2024/09/13 23:17:05 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char **argv, char **envp, int *pipe_fd)
{
	int		infile;
	char	*full_path;

	full_path = realpath(argv[1], NULL);
	if (!full_path)
	{
		ft_putstr_fd("no such file or directory\n", 2);
		exit(EXIT_FAILURE);
	}
	infile = open(full_path, O_RDONLY);
	free(full_path);
	if (infile == -1)
	{
		ft_putstr_fd("no such file or directory\n", 2);
		exit(EXIT_FAILURE);
	}
	if (dup2(infile, STDIN_FILENO) == -1
		|| dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		handle_error();
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(infile);
	execute_pipex(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int *pipe_fd)
{
	int		outfile;
	char	*full_path;

	full_path = get_outfile_path(argv[4]);
	if (!full_path)
	{
		ft_putstr_fd("no such file or directory\n", 2);
		exit(EXIT_FAILURE);
	}
	outfile = open(full_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(full_path);
	if (outfile == -1)
	{
		ft_putstr_fd("no such file or directory\n", 2);
		exit(EXIT_FAILURE);
	}
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1
		|| dup2(outfile, STDOUT_FILENO) == -1)
		handle_error();
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(outfile);
	execute_pipex(argv[3], envp);
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
		ft_putstr_fd("Error: Command not found: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd("\n", 2);
		free_matrix(cmd);
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmd, envp) == -1)
	{
		ft_putstr_fd("Error: Command not found: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd("\n", 2);
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
	int		status;

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
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
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
