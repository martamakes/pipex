/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:40:21 by mvigara           #+#    #+#             */
/*   Updated: 2024/09/13 14:40:47 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
	{
		ft_printf("Error: Invalid number of arguments\n");
		ft_printf("Usage: ./pipex file1 cmd1 cmd2 ... cmdn file2\n");
		ft_printf("   or: ./pipex here_doc LIMITER cmd1 cmd2 ... cmdn file2\n");
		exit(1);
	}
	init_pipex(&pipex, argc, argv);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		setup_here_doc(&pipex, argv);
	else
		setup_files(&pipex, argv);
	if (pipex.input_fd == -1 || pipex.output_fd == -1)
		handle_error();
	dup2(pipex.input_fd, STDIN_FILENO);
	dup2(pipex.output_fd, STDOUT_FILENO);
	close(pipex.input_fd);
	close(pipex.output_fd);
	pipex_process(argc, argv, envp, &pipex);
	return (0);
}
