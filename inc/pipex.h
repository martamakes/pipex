/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:38:06 by mvigara-          #+#    #+#             */
/*   Updated: 2024/09/15 00:36:03 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

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
char	*handle_absolute_path(char **args);
char	*get_path_from_env(char **envp);
char	*search_in_path(char *cmd, char *env_path);
void	handle_permission_error(char *filename);
int		is_quote(char c);
char	*skip_spaces(char **str);
char	*extract_token(char **str);
void	handle_infile_error(char *filename);

#endif