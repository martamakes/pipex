#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft.h"

void	child_process(char **argv, char **envp, int *pipe_fd);
void	parent_process(char **argv, char **envp, int *pipe_fd);
void	execute_pipex(char *argv, char **envp);
void	handle_error(void);
void	free_matrix(char **matrix);
char	*find_path(char *cmd, char **envp);

#endif
