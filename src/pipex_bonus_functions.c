/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:11:28 by mvigara-          #+#    #+#             */
/*   Updated: 2024/09/13 15:12:55 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc(char *limiter, int pipe_fd[2])
{
	char	*line;

	close(pipe_fd[0]);
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
		if (!line)
			exit(1);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			exit(0);
		}
		ft_putstr_fd(line, pipe_fd[1]);
		free(line);
	}
}

void	child_process(char *cmd, char **envp, int input_fd, int output_fd)
{
	char	**args;
	char	*path;

	dup2(input_fd, STDIN_FILENO);
	dup2(output_fd, STDOUT_FILENO);
	close(input_fd);
	close(output_fd);
	args = ft_split(cmd, ' ');
	if (!args)
		handle_error();
	path = find_path(args[0], envp);
	if (!path)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd("\n", 2);
		free_matrix(args);
		exit(127);
	}
	if (execve(path, args, envp) == -1)
	{
		free_matrix(args);
		free(path);
		handle_error();
	}
}

void	execute_cmd(char *cmd, char **envp)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (!args)
		handle_error();
	path = find_path(args[0], envp);
	if (!path)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd("\n", 2);
		free_matrix(args);
		exit(127);
	}
	if (execve(path, args, envp) == -1)
	{
		free_matrix(args);
		free(path);
		handle_error();
	}
}
