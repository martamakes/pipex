/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:41:35 by mvigara-          #+#    #+#             */
/*   Updated: 2024/09/13 14:51:25 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_pipex(t_pipex *pipex, int argc, char **argv)
{
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->here_doc = (ft_strncmp(argv[1], "here_doc", 8) == 0);
	if (pipex->here_doc)
		pipex->start_idx = 3;
	else
		pipex->start_idx = 2;
}

void	setup_here_doc(t_pipex *pipex, char **argv)
{
	int		here_doc_pipe[2];
	pid_t	here_doc_pid;

	if (pipex->argc < 6)
	{
		ft_printf("Error: Invalid number of arguments for here_doc\n");
		exit(1);
	}
	if (pipe(here_doc_pipe) == -1)
		handle_error();
	here_doc_pid = fork();
	if (here_doc_pid == -1)
		handle_error();
	if (here_doc_pid == 0)
		here_doc(argv[2], here_doc_pipe);
	wait(NULL);
	close(here_doc_pipe[1]);
	pipex->input_fd = here_doc_pipe[0];
	pipex->output_fd = open(argv[pipex->argc - 1],
			O_WRONLY | O_CREAT | O_APPEND, 0644);
}

void	setup_files(t_pipex *pipex, char **argv)
{
	pipex->input_fd = open(argv[1], O_RDONLY);
	pipex->output_fd = open(argv[pipex->argc - 1], O_WRONLY | O_CREAT | O_TRUNC,
			0644);
}

void	create_child(char **argv, char **envp, int prev_pipe, int *pipe_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		handle_error();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		child_process(argv[*pipe_fd], envp, prev_pipe, pipe_fd[1]);
	}
	close(pipe_fd[1]);
	if (prev_pipe != STDIN_FILENO)
		close(prev_pipe);
}

void	pipex_process(int argc, char **argv, char **envp, t_pipex *pipex)
{
	int	pipe_fd[2];
	int	prev_pipe;
	int	i;

	prev_pipe = STDIN_FILENO;
	i = pipex->start_idx;
	while (i < argc - 1)
	{
		if (pipe(pipe_fd) == -1)
			handle_error();
		create_child(argv, envp, prev_pipe, pipe_fd);
		prev_pipe = pipe_fd[0];
		i++;
	}
	dup2(prev_pipe, STDIN_FILENO);
	if (prev_pipe != STDIN_FILENO)
		close(prev_pipe);
	execute_cmd(argv[argc - 2], envp);
}
