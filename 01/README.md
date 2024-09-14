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

# Pipex Project

## Overview
The Pipex project is a 42 school assignment that simulates the behavior of shell pipes. It takes input from a file, executes a series of commands, and outputs the result to another file. This project includes both a mandatory part for basic functionality and a bonus part for handling multiple pipes and here_doc input.

## Project Structure
```
.
├── Makefile
├── inc
│   └── pipex.h
├── lib
│   └── libft
│       ├── Makefile
│       ├── inc
│       │   └── libft.h
│       └── src
│           └── [libft source files]
├── src
│   ├── path.c
│   ├── path_utils.c
│   ├── pipex.c
│   └── utils.c
└── README.md
```

## Mandatory Part

### Usage
```
./pipex file1 cmd1 cmd2 file2
```
This behaves like: `< file1 cmd1 | cmd2 > file2`

### Key Functions
1. `main` (in pipex.c): Argument parsing and process initiation.
2. `child_process` (in pipex.c): Handles the first command execution.
3. `parent_process` (in pipex.c): Handles the second command execution.
4. `execute_command` (in pipex.c): Executes a single command.
5. `find_path` (in path.c): Locates the full path of a command.
6. `find_executable` (in path_utils.c): Searches for an executable in the system PATH.
7. `join_path` (in path_utils.c): Combines directory and command to form a full path.
8. `get_file_path` (in path.c): Resolves relative and absolute file paths.
9. `handle_error` (in utils.c): Unified error handling function.

## Bonus Part (if implemented)

### Usage
```
./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
./pipex here_doc LIMITER cmd cmd1 file
```

### Additional Features
- Multiple pipes handling
- Here_doc functionality (see [here_doc.md](here_doc.md) for details)

## Key Concepts

1. **Pipes**: Inter-process communication mechanism.
2. **Fork**: Creation of child processes.
3. **File Descriptors**: Management for input/output redirection.
4. **Execve**: Execution of commands.
5. **Environment Variables**: Used for locating command paths.

## Compilation

```bash
make        # Compile mandatory part
make bonus  # Compile bonus part (if implemented)
make clean  # Remove object files
make fclean # Remove object files and executables
make re     # Recompile everything
```

## Error Handling
The program handles various error scenarios, including:
- Incorrect number of arguments
- File access issues
- Command not found
- Execution failures
- Empty arguments

## Testing
A comprehensive test suite is recommended to ensure proper functionality across various scenarios. Consider testing:
- Basic functionality with simple commands
- Error handling for non-existent files and commands
- Handling of complex commands with arguments
- Proper closing of file descriptors and memory management

## Notes
- This project adheres to the 42 coding norms.
- Only allowed functions are used as per the project requirements.
- Proper memory management is crucial, especially when handling dynamic allocations.
- The project uses a custom libft library, located in the `lib/libft` directory.

For more detailed information on specific components like here_doc, refer to the additional documentation files in the project directory.

## Libft Integration
The project uses a custom libft library for various string and memory operations. Make sure the libft is properly compiled before building the main project. The Makefile is set up to handle this dependency.

## Contribution
This project is part of the 42 curriculum and is meant for educational purposes. If you're a fellow 42 student, make sure to develop your own solution to meet the project requirements.

### Pseudocode

Pseudo Code:

1. Main Function:
   - Parse and validate arguments
   - Set up pipes
   - Fork for child process
   - Execute child process
   - Execute parent process
   - Wait for child process
   - Clean up and exit

2. Child Process:
   - Open input file
   - Redirect stdin to input file
   - Redirect stdout to pipe write end
   - Close unused file descriptors
   - Find and execute first command

3. Parent Process:
   - Open output file
   - Redirect stdin from pipe read end
   - Redirect stdout to output file
   - Close unused file descriptors
   - Find and execute second command

4. Find Path:
   - Get PATH from environment
   - Split PATH into directories
   - For each directory:
     - Construct full path to command
     - Check if file exists and is executable
     - Return full path if found
   - Return NULL if not found

5. Execute Command:
   - Split command string into arguments
   - Find full path of command
   - Use execve to run command

Now, let's look at the key parts of your implementation:

1. Main Function (pipex.c):

```c
int main(int argc, char **argv, char **envp)
{
    if (argc != 5)
    {
        ft_putstr_fd("Error: Bad arguments\n", 2);
        ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
        exit(EXIT_FAILURE);
    }
    check_empty_args(argc, argv);
    setup_pipes_and_execute(argv, envp);
    return (0);
}
```

This function checks for the correct number of arguments, ensures no arguments are empty, and then calls `setup_pipes_and_execute`.

2. Setup Pipes and Execute (pipex.c):

```c
void setup_pipes_and_execute(char **argv, char **envp)
{
    int     pipe_fd[2];
    pid_t   pid1;
    pid_t   pid2;

    if (pipe(pipe_fd) == -1)
        handle_error();
    pid1 = fork();
    if (pid1 == -1)
        handle_error();
    if (pid1 == 0)
        child_process(argv, envp, pipe_fd);
    pid2 = fork();
    if (pid2 == -1)
        handle_error();
    if (pid2 == 0)
        parent_process(argv, envp, pipe_fd);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}
```

This function creates a pipe, forks twice to create two child processes, and waits for both to complete.

3. Child Process (pipex.c):

```c
void child_process(char **argv, char **envp, int *pipe_fd)
{
    int     infile;
    char    *path;

    infile = open(argv[1], O_RDONLY);
    if (infile == -1)
    {
        print_error(argv[1], errno);
        infile = open("/dev/null", O_RDONLY);
        if (infile == -1)
            handle_error();
    }
    if (dup2(infile, STDIN_FILENO) == -1 || dup2(pipe_fd[1], STDOUT_FILENO) == -1)
        handle_error();
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    close(infile);
    path = find_path(argv[2], envp);
    if (!path)
    {
        print_error(argv[2], ENOENT);
        exit(EXIT_FAILURE);
    }
    execute_command(path, argv[2], envp);
}
```

This function handles the first command. It opens the input file, redirects stdin and stdout, and executes the command.

4. Parent Process (pipex.c):

```c
void parent_process(char **argv, char **envp, int *pipe_fd)
{
    int     outfile;
    char    *path;

    outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile == -1)
    {
        print_error(argv[4], errno);
        outfile = open("/dev/null", O_WRONLY);
        if (outfile == -1)
            handle_error();
    }
    if (dup2(pipe_fd[0], STDIN_FILENO) == -1 || dup2(outfile, STDOUT_FILENO) == -1)
        handle_error();
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    close(outfile);
    path = find_path(argv[3], envp);
    if (!path)
    {
        print_error(argv[3], ENOENT);
        exit(EXIT_FAILURE);
    }
    execute_command(path, argv[3], envp);
}
```

This function handles the second command. It opens the output file, redirects stdin and stdout, and executes the command.

5. Find Path (path.c):

```c
char *find_path(char *cmd, char **envp)
{
    char    **paths;
    char    *path;
    char    *first_arg;
    int     i;

    if (!cmd || cmd[0] == '\0')
        return (NULL);
    first_arg = ft_split(cmd, ' ')[0];
    if (ft_strchr(first_arg, '/'))
        return (ft_strdup(first_arg));
    i = 0;
    while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
        i++;
    if (!envp[i])
        return (NULL);
    paths = ft_split(envp[i] + 5, ':');
    if (!paths)
        return (NULL);
    path = find_executable(paths, first_arg);
    free_matrix(paths);
    free(first_arg);
    return (path);
}
```

This function finds the full path of a command by searching in the directories specified in the PATH environment variable.

6. Execute Command (pipex.c):

```c
void execute_command(char *path, char *argv, char **envp)
{
    char    **cmd;

    cmd = ft_split(argv, ' ');
    if (!cmd)
        handle_error();
    if (execve(path, cmd, envp) == -1)
    {
        print_error(cmd[0], errno);
        free_matrix(cmd);
        free(path);
        exit(EXIT_FAILURE);
    }
}
```

This function splits the command string into arguments and uses execve to execute the command.

Your implementation follows the pseudo code structure closely. You've added robust error handling throughout the code, using functions like `handle_error` and `print_error` to manage and report errors. You've also implemented helper functions like `find_executable` and `join_path` to assist with finding and constructing command paths.

The use of libft functions (like ft_split, ft_strncmp, etc.) shows good integration with your custom library. Overall, your code demonstrates a solid understanding of process creation, file descriptor manipulation, and command execution in a Unix-like environment.


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