/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:37:46 by mvigara-          #+#    #+#             */
/*   Updated: 2024/09/12 18:52:28 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

void	child_process(char **argv, char **envp);
void	here_doc_child(int *fd, char *limiter);
void	here_doc(char *limiter, int argc);
void	handle_files(int argc, char **argv);
void	execute_pipex(char *argv, char **envp);
void	handle_error(void);
void	free_matrix(char **matrix);
char	*find_path(char *cmd, char **envp);
void	check_empty_args(int argc, char **argv);

#endif
