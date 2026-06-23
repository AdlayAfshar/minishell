# Minishell

Minishell is a small Unix shell written in C as part of the 42 curriculum. It
implements an interactive prompt, command parsing, environment expansion,
redirections, heredocs, pipelines, signal handling, and the required built-in
commands.

The goal is to reproduce the core behavior of a POSIX-style shell for the 42
`minishell` project, not to replace `bash` completely.



https://github.com/user-attachments/assets/0c22b530-59b6-476d-b6a9-7ad3dc88ae95



## Features

- Interactive prompt powered by GNU Readline
- Command history
- Lexing and parsing for words, pipes, redirections, append redirections,
  heredocs, and semicolons
- Single and double quote handling
- Environment variable expansion with `$VAR`
- Last exit status expansion with `$?`
- External command execution through `PATH`
- Pipelines with `|`
- Input and output redirections:
  - `<`
  - `>`
  - `>>`
  - `<<`
- Heredoc support, including quoted delimiter detection
- Signal handling for interactive mode and heredocs
- Terminal mode handling with `termios`
- Built-in commands:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

## Requirements

You need a C compiler, `make`, and the GNU Readline development library.

### macOS

Install Readline with Homebrew:

```sh
brew install readline
```

Install the Xcode command line tools if you do not already have a compiler:

```sh
xcode-select --install
```

### Linux

On Debian/Ubuntu-based systems, install:

```sh
sudo apt update
sudo apt install build-essential libreadline-dev
```

On Fedora:

```sh
sudo dnf install gcc make readline-devel
```

## Build

From the project root, run:

```sh
make
```

This builds the `libft` static library and creates the `minishell` executable.

Useful Makefile targets:

```sh
make clean
```

Removes object files.

```sh
make fclean
```

Removes object files, `libft.a`, and the `minishell` executable.

```sh
make re
```

Rebuilds the project from scratch.

## Run

Start the shell with:

```sh
./minishell
```

You should see:

```text
minishell>
```

Example commands:

```sh
echo hello world
pwd
cd ..
export NAME=minishell
echo "$NAME"
echo $?
ls -la | grep src
cat < input.txt
echo hello > output.txt
echo again >> output.txt
cat << EOF
hello
EOF
```

Exit the shell with:

```sh
exit
```

or press `Ctrl-D` on an empty prompt.

## Built-ins

| Built-in | Description |
| --- | --- |
| `echo` | Prints arguments, with support for `-n` |
| `cd` | Changes the current directory and updates `PWD` / `OLDPWD` |
| `pwd` | Prints the current working directory |
| `export` | Adds or updates environment variables |
| `unset` | Removes environment variables |
| `env` | Prints the current environment |
| `exit` | Exits the shell with an optional status code |

## Supported Syntax

Minishell supports the core syntax required by the 42 project:

```sh
command arg1 arg2
command1 | command2 | command3
command < infile
command > outfile
command >> outfile
command << LIMITER
echo "$HOME"
echo '$HOME'
echo $?
```

Single quotes preserve literal text. Double quotes allow variable expansion.

## Signals

Interactive behavior is handled separately from child process and heredoc modes:

- `Ctrl-C` interrupts the current prompt or running command
- `Ctrl-D` exits the shell from an empty prompt
- `Ctrl-\` is ignored in the interactive prompt

## Project Structure

```text
.
├── include/
│   ├── builtins.h
│   ├── env.h
│   ├── exec.h
│   ├── expand.h
│   ├── heredoc.h
│   ├── lexer.h
│   ├── parser.h
│   ├── shell.h
│   ├── signals.h
│   └── terminal.h
├── libft/
├── src/
│   ├── builtins/
│   ├── env/
│   ├── exec/
│   ├── expand/
│   ├── heredoc/
│   ├── lexer/
│   ├── parser/
│   ├── shell/
│   ├── signals/
│   └── terminal/
└── Makefile
```

## Notes

- The project can be compiled and run on both macOS and Linux when Readline is
  installed and the Makefile points to the correct Readline include/library
  paths.
- The current Makefile includes Homebrew's Apple Silicon Readline paths:
  `/opt/homebrew/opt/readline/include` and `/opt/homebrew/opt/readline/lib`.
  On Linux, or on Intel Macs using `/usr/local/opt/readline`, those paths may
  need to be adjusted.
- This project intentionally implements a limited shell subset for the 42
  assignment. Advanced Bash features such as globbing, command substitution,
  job control, logical operators, and subshells are not implemented.
