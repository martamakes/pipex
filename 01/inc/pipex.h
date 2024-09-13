/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:38:06 by mvigara-          #+#    #+#             */
/*   Updated: 2024/09/13 21:56:43 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

void	child_process(char **argv, char **envp, int *pipe_fd);
void	parent_process(char **argv, char **envp, int *pipe_fd);
void	execute_pipex(char *argv, char **envp);
void	handle_error(void);
void	free_matrix(char **matrix);
char	*find_path(char *cmd, char **envp);
void	check_empty_args(int argc, char **argv);
char	*get_outfile_path(char *outfile_arg);

#endif