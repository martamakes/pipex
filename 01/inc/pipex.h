/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marta <marta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:38:06 by mvigara-          #+#    #+#             */
/*   Updated: 2024/09/14 18:56:50 by marta            ###   ########.fr       */
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

void	child_process(char **argv, char **envp, int *pipe_fd);
void	parent_process(char **argv, char **envp, int *pipe_fd);
void	execute_command(char *path, char *argv, char **envp);
void	setup_pipes_and_execute(char **argv, char **envp);
void	handle_error(char *context, char *detail, int error_code);
void	free_matrix(char **matrix);
int		open_file(char *file, int flags);
char	*find_path(char *cmd, char **envp);
char	*get_file_path(char *file, char **envp);
char	*handle_parent_dir(char *cwd, char *file, char **envp);
char	*get_current_dir(char **envp);
char	*find_executable(char **paths, char *cmd);
char	*join_path(char *dir, char *cmd);
char	**parse_command(char *cmd);

#endif