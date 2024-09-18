/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:55:58 by marta             #+#    #+#             */
/*   Updated: 2024/09/15 00:39:50 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_infile(char *filename)
{
	int	infile;

	infile = open(filename, O_RDONLY);
	if (infile == -1)
	{
		if (errno == EACCES)
			handle_permission_error(filename);
		else if (errno == ENOENT)
			handle_infile_error(filename);
		else
			handle_error(NULL, filename, errno);
		return (-1);
	}
	return (infile);
}

void	parent_process(char **argv, char **envp, int *pipe_fd)
{
	int		outfile;
	char	*path;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		if (errno == EACCES)
			handle_permission_error(argv[4]);
		else
			handle_error(NULL, argv[4], errno);
		exit(1);
	}
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1 || dup2(outfile, STDOUT_FILENO)
		== -1)
		handle_error("Dup2 failed", NULL, errno);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(outfile);
	path = find_path(argv[3], envp);
	if (!path)
		handle_error("No such file or directory", argv[3], ENOENT);
	execute_command(path, argv[3], envp);
}

void	child_process(char **argv, char **envp, int *pipe_fd)
{
	int		infile;
	char	*path;

	infile = open_infile(argv[1]);
	if (infile == -1)
		infile = open("/dev/null", O_RDONLY);
	if (dup2(infile, STDIN_FILENO) == -1 || dup2(pipe_fd[1], STDOUT_FILENO)
		== -1)
		handle_error("Dup2 failed", NULL, errno);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(infile);
	path = find_path(argv[2], envp);
	if (!path)
		handle_error(NULL, argv[2], ENOENT);
	execute_command(path, argv[2], envp);
}

static char	*get_cmd_name(char *path)
{
	char	*cmd_name;

	cmd_name = ft_strrchr(path, '/');
	if (cmd_name)
		return (ft_strdup(cmd_name + 1));
	return (ft_strdup(path));
}

void	execute_command(char *path, char *argv, char **envp)
{
	char	**cmd;
	char	*cmd_name;

	cmd = parse_command(argv);
	if (!cmd)
		handle_error("Memory allocation failed", NULL, errno);
	if (!cmd[0])
	{
		cmd_name = get_cmd_name(path);
		if (!cmd_name)
		{
			free_matrix(cmd);
			free(path);
			handle_error("Memory allocation failed", NULL, errno);
		}
	}
	if (execve(path, cmd, envp) == -1)
	{
		free_matrix(cmd);
		free(path);
		handle_error("execve", cmd[0], errno);
	}
}
