/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipex - here_doc                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara-@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 01 agosto 2024                          #+#    #+#             */
/*   Updated: 12 septiembre 2024                      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# Here Document (here_doc) Explanation

## What is a Here Document?

A here document, often referred to as "here_doc" or "heredoc", is a way of specifying a multiline string literal in shell scripts and command-line interfaces. It allows you to input multiple lines of text directly into a command or script, without having to store it in a separate file.

## Basic Syntax

The basic syntax for a here document in a shell is:

```bash
command << DELIMITER
line 1
line 2
line 3
DELIMITER
```

Here, `DELIMITER` can be any word you choose (e.g., EOF, END, STOP). The shell will read all lines between the two DELIMITERs and pass them as input to the command.

## Usage in Shell

In a shell, you might use a here document like this:

```bash
cat << EOF
Hello, world!
This is a multi-line
string using here_doc.
EOF
```

This would output:
```
Hello, world!
This is a multi-line
string using here_doc.
```

## Here Documents in Pipex

In the context of the pipex project, implementing here_doc functionality means allowing the user to input data directly into the command pipeline, rather than reading from an input file.

For example, a command like this:

```bash
./pipex here_doc LIMITER cmd1 cmd2 outfile
```

Should behave similarly to:

```bash
cmd1 << LIMITER | cmd2 >> outfile
```

## Implementation in Pipex

To implement here_doc in pipex:

1. Detect if the first argument is "here_doc".
2. If so, read input from the user until the LIMITER is encountered.
3. Use this input as the source for the first command, instead of reading from a file.
4. Open the output file in append mode (O_APPEND) instead of truncate mode (O_TRUNC).

## Key Considerations

1. **Input Reading**: You'll need to read input line by line until the limiter is encountered. The `get_next_line` function is useful for this.

2. **Pipe Usage**: You'll likely need to create a pipe to pass the here_doc input to the first command.

3. **Process Management**: You might need to fork an additional process to handle reading the here_doc input.

4. **Error Handling**: Ensure you handle cases where the limiter is never encountered, or if there are issues with reading input.

5. **Memory Management**: Be careful to free any allocated memory, especially if you're storing the input before passing it to the command.

By implementing here_doc functionality, your pipex program becomes more versatile, allowing users to input data directly into the command pipeline without needing an input file.

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipex - here_doc                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvigara <mvigara-@student.42madrid.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 01 agosto 2024                          #+#    #+#             */
/*   Updated: 12 septiembre 2024                      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */