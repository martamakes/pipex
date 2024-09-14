/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marta <marta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:38:06 by mvigara-          #+#    #+#             */
/*   Updated: 2024/09/14 12:00:26 by marta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include "libft.h"

// pipex.c
void	child_process(char **argv, char **envp, int *pipe_fd);
void	parent_process(char **argv, char **envp, int *pipe_fd);
void	execute_command(char *path, char *argv, char **envp);
void	setup_pipes_and_execute(char **argv, char **envp);

// utils.c
void	check_empty_args(int argc, char **argv);
void	handle_error(void);
void	free_matrix(char **matrix);
void	print_error(char *arg, int error_code);
int		open_file(char *file, int flags);

// path.c
char	*find_path(char *cmd, char **envp);
char	*get_file_path(char *file, char **envp);
char	*handle_parent_dir(char *cwd, char *file, char **envp);
char	*get_current_dir(char **envp);

// path_utils.c
char	*find_executable(char **paths, char *cmd);
char	*join_path(char *dir, char *cmd);

#endif