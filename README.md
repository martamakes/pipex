/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PIPEX PROJECT                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara-@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 01 agosto 2024                          #+#    #+#             */
/*   Updated: 12 septiembre 2024                      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# Pipex Project

## Overview
The Pipex project is a program that simulates the behavior of the shell pipe command. It takes input from a file, executes a series of commands, and outputs the result to another file. This project includes both a mandatory part for basic functionality and a bonus part for handling multiple pipes and here_doc input.

## Mandatory Part

### Usage
```
./pipex file1 cmd1 cmd2 file2
```
This should behave like: `< file1 cmd1 | cmd2 > file2`

### Implementation

The mandatory part is implemented using the following key functions:

1. `main`: Handles argument parsing and initiates the piping process.
2. `child_process`: Handles the first command execution.
3. `parent_process`: Handles the second command execution.
4. `execute_pipex`: Executes a single command.
5. `find_path`: Finds the full path of a command.

### Pseudocode

```
function main(argc, argv, envp)
    if argc is not 5
        print usage error and exit
    create pipe
    fork process
    if child process
        call child_process(argv, envp, pipe)
    else
        wait for child
        call parent_process(argv, envp, pipe)

function child_process(argv, envp, pipe)
    open input file
    redirect stdin to input file
    redirect stdout to pipe write end
    close unused file descriptors
    execute_pipex(argv[2], envp)

function parent_process(argv, envp, pipe)
    open output file
    redirect stdin to pipe read end
    redirect stdout to output file
    close unused file descriptors
    execute_pipex(argv[3], envp)

function execute_pipex(cmd, envp)
    parse command into arguments
    find full path of command
    if command not found
        exit with appropriate error code
    execute command using execve

function find_path(cmd, envp)
    extract PATH from environment
    for each directory in PATH
        construct full path
        if file exists and is executable
            return full path
    return NULL if not found
```

## Bonus Part

### Usage
```
./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
./pipex here_doc LIMITER cmd cmd1 file
```

### Implementation

The bonus part extends the mandatory implementation with these additional functions:

1. `child_process`: Modified to handle multiple pipes.
2. `here_doc`: Handles [here_doc](here_doc.md) input.
3. `handle_files`: Manages file opening for both regular and here_doc modes.



### Pseudocode

```
function main(argc, argv, envp)
    if argc < 5
        print usage error and exit
    handle_files(argc, argv)
    for each command (excluding first and last)
        call child_process(command, envp)
    execute_pipex(last command, envp)

function child_process(cmd, envp)
    create new pipe
    fork process
    if child
        redirect stdout to pipe write end
        execute_pipex(cmd, envp)
    else
        redirect stdin to pipe read end
        wait for child

function here_doc(limiter, argc)
    create pipe
    fork process
    if child
        read input until limiter is found
        write input to pipe
    else
        redirect stdin to pipe read end

function handle_files(argc, argv)
    if first argument is "here_doc"
        open output file in append mode
        call here_doc
    else
        open input and output files
        redirect stdin to input file
    redirect stdout to output file

function execute_pipex(cmd, envp)
    // Same as in mandatory part
```

## Key Points

1. The project uses fork() and pipe() to create child processes and establish communication between them.
2. File descriptors are carefully managed to ensure proper redirection of input and output.
3. The bonus part extends the functionality to handle multiple commands and the here_doc feature.
4. Error handling is implemented throughout to manage various failure scenarios.
5. The project adheres to the 42 coding norms and uses only allowed functions.

## New Functions and Concepts for Pipex Project

## New Allowed Functions

### 1. `pipe`
```c
int pipe(int pipefd[2]);
```
- Creates a pipe, a unidirectional data channel that can be used for interprocess communication.
- `pipefd[0]` is the read end of the pipe.
- `pipefd[1]` is the write end of the pipe.
- Returns 0 on success, -1 on error.

### 2. `fork`
```c
pid_t fork(void);
```
- Creates a new process by duplicating the calling process.
- Returns 0 in the child process, child's PID in the parent process, or -1 on error.

### 3. `dup2`
```c
int dup2(int oldfd, int newfd);
```
- Duplicates a file descriptor.
- Makes `newfd` be the copy of `oldfd`, closing `newfd` first if necessary.
- Returns the new descriptor on success, -1 on error.

### 4. `execve`
```c
int execve(const char *pathname, char *const argv[], char *const envp[]);
```
- Executes the program pointed to by `pathname`.
- `argv` is an array of argument strings passed to the new program.
- `envp` is an array of strings, conventionally of the form key=value, which are passed as environment to the new program.
- Does not return on success, returns -1 on error.

### 5. `wait` and `waitpid`
```c
pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);
```
- Suspends execution of the calling process until a child process terminates.
- `wait` waits for any child process.
- `waitpid` can wait for a specific child process.
- Returns the PID of the terminated child on success, -1 on error.

## Child and Parent Processes

In Unix-like operating systems, processes can create new processes using the `fork` system call. This creates a child process that is an exact copy of the parent process.

### Parent Process
- The original process that calls `fork`.
- Continues executing from the point immediately after the `fork` call.
- Can use `wait` or `waitpid` to wait for the child process to terminate.

### Child Process
- The new process created by `fork`.
- Is an exact copy of the parent process at the time of `fork`.
- Starts executing from the point immediately after the `fork` call.
- Often uses `execve` to replace its program with a new one.

### Use of Processes in Pipex

1. The main process (parent) creates a child process using `fork`.
2. The child process handles the first command:
   - Redirects input from the input file.
   - Redirects output to the write end of the pipe.
   - Executes the first command using `execve`.
3. The parent process handles the second command:
   - Waits for the child process to finish.
   - Redirects input from the read end of the pipe.
   - Redirects output to the output file.
   - Executes the second command using `execve`.

This setup allows the output of the first command to be passed as input to the second command, simulating the pipe behavior of the shell.

## Environment Paths

Environment paths are typically stored in the `PATH` environment variable. In the pipex project, we need to find the full path of the commands to execute them.

### Getting Environment Paths

1. The `envp` parameter in the main function provides access to the environment variables:
   ```c
   int main(int argc, char *argv[], char *envp[])
   ```

2. We need to find the `PATH` variable in the `envp` array:
   ```c
   char *path_var = NULL;
   int i = 0;
   while (envp[i] != NULL)
   {
       if (ft_strncmp(envp[i], "PATH=", 5) == 0)
       {
           path_var = envp[i] + 5;  // Skip "PATH="
           break;
       }
       i++;
   }
   ```

3. Once we have the `PATH` string, we can split it into individual directories:
   ```c
   char **paths = ft_split(path_var, ':');
   ```

4. To find a command, we iterate through these paths and check if the command exists:
   ```c
   char *find_command(char *cmd, char **paths)
   {
       char *full_path;
       int i;

       i = 0;
       while (paths[i] != NULL)
       {
           full_path = ft_strjoin(paths[i], "/");
           full_path = ft_strjoin(full_path, cmd);
           if (access(full_path, X_OK) == 0)
           {
               return (full_path);
           }
           free(full_path);
           i++;
       }
       return (NULL);
   }
   ```

This process allows us to locate the full path of a command, which is necessary for using `execve` to execute the command.

Remember to free any allocated memory and handle potential errors in your actual implementation. Also, ensure that you're checking for NULL returns from functions like `ft_strjoin` and handling those cases appropriately.

## How to Compile

To compile the Pipex project, follow these steps:

1. Clone the repository:
   ```
   git clone <repository_url> pipex
   cd pipex
   ```

2. Compile the mandatory part:
   ```
   make
   ```
   This will create the `pipex` executable.

3. Compile the bonus part (if implemented):
   ```
   make bonus
   ```
   This will create the `pipex_bonus` executable.

4. To remove object files:
   ```
   make clean
   ```

5. To remove object files and executables:
   ```
   make fclean
   ```

6. To recompile everything:
   ```
   make re
   ```

### Compilation Notes

- The project uses `cc` as the C compiler.
- Compilation flags include `-Wall -Wextra -Werror`.
- The project links against the libft library, which should be in the `lib/libft` directory.

Make sure you have the necessary permissions to execute the Makefile and that you have a C compiler installed on your system.

## Usage

### Mandatory Part
```
./pipex infile cmd1 cmd2 outfile
```

### Bonus Part (if implemented)
```
./pipex_bonus infile cmd1 cmd2 cmd3 ... cmdn outfile
./pipex_bonus here_doc LIMITER cmd cmd1 outfile
```