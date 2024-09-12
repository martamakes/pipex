/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marta <marta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:37:46 by mvigara-          #+#    #+#             */
/*   Updated: 2024/09/12 20:49:28 by marta            ###   ########.fr       */
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

typedef struct s_pipex
{
    int argc;
    char **argv;
    int here_doc;
    int start_idx;
    int input_fd;
    int output_fd;
} t_pipex;

void    execute_cmd(char *cmd, char **envp);
void    child_process(char *cmd, char **envp, int input_fd, int output_fd);
void    here_doc(char *limiter, int pipe_fd[2]);
void    handle_error(void);
char    *find_path(char *cmd, char **envp);
void    free_matrix(char **matrix);

// New functions in pipex_bonus_utils.c
void    init_pipex(t_pipex *pipex, int argc, char **argv);
void    setup_here_doc(t_pipex *pipex, char **argv);
void    setup_files(t_pipex *pipex, char **argv);
void    pipex_process(int argc, char **argv, char **envp, t_pipex *pipex);

#endif
