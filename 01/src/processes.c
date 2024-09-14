/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marta <marta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:55:58 by marta             #+#    #+#             */
/*   Updated: 2024/09/14 18:56:03 by marta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_infile_error(char *filename, int error_code)
{
	if (error_code == EACCES)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
	else
		handle_error(NULL, filename, error_code);
}

static int	open_infile(char *filename)
{
	int	infile;

	infile = open(filename, O_RDONLY);
	if (infile == -1)
	{
		handle_infile_error(filename, errno);
		infile = open("/dev/null", O_RDONLY);
		if (infile == -1)
			handle_error("Error opening /dev/null", NULL, errno);
	}
	return (infile);
}

void	child_process(char **argv, char **envp, int *pipe_fd)
{
	int		infile;
	char	*path;

	infile = open_infile(argv[1]);
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

void	parent_process(char **argv, char **envp, int *pipe_fd)
{
	int		outfile;
	char	*path;

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
		handle_error("No such file or directory", argv[3], ENOENT);
	execute_command(path, argv[3], envp);
}

void	execute_command(char *path, char *argv, char **envp)
{
	char	**cmd;

	cmd = parse_command(argv);
	if (!cmd)
		handle_error("Memory allocation failed", NULL, errno);
	if (execve(path, cmd, envp) == -1)
	{
		free_matrix(cmd);
		free(path);
		handle_error("execve", cmd[0], errno);
	}
}
