/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marta <marta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:40:21 by mvigara           #+#    #+#             */
/*   Updated: 2024/09/12 10:25:11 by marta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_process(char *argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		handle_error();
	pid = fork();
	if (pid == -1)
		handle_error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute_pipex(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	here_doc_child(int *fd, char *limiter)
{
	char	*line;

	close(fd[0]);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 &&
			line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	exit(EXIT_SUCCESS);
}

void	here_doc(char *limiter, int argc)
{
	pid_t	reader;
	int		fd[2];

	if (argc < 6)
		exit(1);
	if (pipe(fd) == -1)
		handle_error();
	reader = fork();
	if (reader == -1)
		handle_error();
	if (reader == 0)
		here_doc_child(fd, limiter);
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
		close(fd[0]);
	}
}

void	handle_files(int argc, char **argv)
{
	int	infile;
	int	outfile;

	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		here_doc(argv[2], argc);
	}
	else
	{
		infile = open(argv[1], O_RDONLY);
		outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (infile == -1)
			handle_error();
		dup2(infile, STDIN_FILENO);
	}
	if (outfile == -1)
		handle_error();
	dup2(outfile, STDOUT_FILENO);
}

int	main(int argc, char **argv, char **envp)
{
	int	i;

	if (argc < 5)
	{
		ft_putstr_fd("Error: Bad arguments\n", 2);
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 ... cmdn file2\n", 1);
		ft_putstr_fd("   or: ./pipex here_doc LIMITER cmd cmd1 file\n", 1);
		exit(1);
	}
	handle_files(argc, argv);
	i = 2;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		i = 3;
	while (i < argc - 2)
		child_process(argv[i++], envp);
	execute_pipex(argv[argc - 2], envp);
	return (0);
}