/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara- <mvigara-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:38:06 by mvigara-          #+#    #+#             */
/*   Updated: 2024/09/13 21:10:56 by mvigara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft.h"

// Functions from pipex.c
void	execute_cmd(char *argv, char **envp);

// Functions from utils.c
void	check_empty_args(int argc, char **argv);
void	free_matrix(char **matrix);
char	*find_path(char *cmd, char **envp);

#endif
