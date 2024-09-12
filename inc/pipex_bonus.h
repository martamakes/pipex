#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft.h"

void	child_process(char *argv, char **envp);
void	here_doc_child(int *fd, char *limiter);
void	here_doc(char *limiter, int argc);
void	handle_files(int argc, char **argv);
void	execute_pipex(char *argv, char **envp);
void	handle_error(void);
void	free_matrix(char **matrix);
char	*find_path(char *cmd, char **envp);

#endif
