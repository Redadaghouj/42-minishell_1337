# ☢️ Shellnobyl: Minishell - 1337 Project

[![1337 Badge](https://img.shields.io/badge/1337-Project-blue)](https://www.42network.org/)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen) ![Grade](https://img.shields.io/badge/Grade-0%2F100-progress)

## 📜 Project Overview

Minishell is a project from the 42 Network that involves creating a simple command-line interpreter, similar to a basic version of Bash. The project aims to provide a deep understanding of processes and file descriptors.

## 🚀 Features

### ✅ Mandatory Part

  * **Prompt and History:** Displays a prompt when waiting for a new command and has a working history.
  * **Command Execution:** Searches for and launches the right executable based on the `PATH` variable or using a relative or absolute path.
  * **Quotes:** Handles single quotes (`'`) to prevent the shell from interpreting metacharacters and double quotes (`"`) which prevents metacharacter interpretation except for the dollar sign (`$`).
  * **Redirections:** Implements input redirection (`<`), output redirection (`>`), appending output redirection (`>>`), and heredoc (`<<`) which reads input until a delimiter is seen.
  * **Pipes:** Supports pipes (`|`) where the output of each command is connected to the input of the next.
  * **Environment Variables:** Expands environment variables (`$`) and the exit status variable (`$?`).
  * **Signal Handling:** Handles `ctrl-C`, `ctrl-D`, and `ctrl-\` like in Bash.
  * **Built-in Commands:** Implements the following built-in commands:
      * `echo` with the `-n` option
      * `cd` with a relative or absolute path
      * `pwd` with no options
      * `export`
      * `unset`
      * `env` with no options or arguments
      * `exit`

### ➕ Bonus Part

  * **Wildcards:** Supports wildcards (`*`) for file name expansion in the current working directory.

## 📂 Repository Structure

```plaintext
📦 42-minishell_1337
├── 📂 bonus
│   ├── 📂 include
│   ├── 📂 src
│   │   ├── 📂 execution
│   │   │   ├── 📂 builtins
│   │   │   ├── 📂 pipe
│   │   │   └── 📂 redirection
│   │   ├── 📂 parsing
│   │   │   ├── 📂 env
│   │   │   ├── 📂 expansion
│   │   │   ├── 📂 heredoc
│   │   │   ├── 📂 lexer
│   │   │   └── 📂 parser
│   │   └── 📂 utils
│   │       └── 📂 gnl
├── 📂 mandatory
│   ├── 📂 include
│   │   ├── env.h
│   │   ├── execution.h
│   │   ├── expansion.h
│   │   ├── heredoc.h
│   │   ├── lexer.h
│   │   ├── minishell.h
│   │   └── parser.h
│   └── 📂 src
│       ├── 📂 execution
│       │   ├── execution.c
│       │   ├── execution_utils.c
│       │   ├── 📂 builtins
│       │   │   ├── cd.c
│       │   │   ├── echo.c
│       │   │   ├── env.c
│       │   │   ├── exit.c
│       │   │   ├── export.c
│       │   │   ├── pwd.c
│       │   │   └── unset.c
│       │   ├── 📂 pipe
│       │   │   └── pipe.c
│       │   └── 📂 redirection
│       │       ├── ambiguous_redir.c
│       │       └── redir.c
│       ├── minishell.c
│       ├── minishell_utils.c
│       ├── 📂 parsing
│       │   ├── 📂 env
│       │   │   ├── env.c
│       │   │   └── env_lists.c
│       │   ├── 📂 expansion
│       │   │   ├── append_args.c
│       │   │   ├── expansion.c
│       │   │   ├── expansion_utils.c
│       │   │   └── quote_cleaner.c
│       │   ├── 📂 heredoc
│       │   │   ├── heredoc.c
│       │   │   └── heredoc_signals.c
│       │   ├── 📂 lexer
│       │   │   ├── check_operator.c
│       │   │   ├── tokenize_input.c
│       │   │   └── tokenize_lists.c
│       │   └── 📂 parser
│       │       ├── check_syntax.c
│       │       ├── parser.c
│       │       ├── parser_lists.c
│       │       └── redir_lists.c
│       └── 📂 utils
│           ├── ft_atoi.c
│           ├── ft_isalnum.c
│           ├── ft_isalpha.c
│           ├── ft_isdigit.c
│           ├── ft_itoa.c
│           ├── ft_putstr_fd.c
│           ├── ft_split.c
│           ├── ft_strchr.c
│           ├── ft_strcmp.c
│           ├── ft_strdup.c
│           ├── ft_strjoin.c
│           ├── ft_strlen.c
│           ├── ft_strncmp.c
│           ├── ft_substr.c
│           ├── 📂 gnl
│           │   ├── get_next_line.c
│           │   ├── get_next_line.h
│           │   └── get_next_line_utils.c
│           └── rb_strjoin.c
├── Makefile
└── 📂 subject
    ├── en.subject.pdf
    └── en.subject_dark_mode.pdf
```

## 🛠️ Installation & Compilation

### 📌 Mandatory

```bash
make
```

Generates the `minishell` executable.

### 📌 Bonus

```bash
make bonus
```

Generates the `minishell` executable with bonus features included.

### 🔧 Cleanup

```bash
make clean      # Removes object files
make fclean     # Removes all binaries and object files
make re         # Performs a full rebuild
```

## 📖 Usage Examples

```bash
./minishell
```

## 📏 Rules

  * **Global Variables:** The use of global variables is limited to one, which must only be used to indicate a received signal number.
  * **Memory Management:** All heap-allocated memory must be properly freed, and memory leaks are not tolerated.
  * **Norm:** The project must be written in C and be Norminette-compliant.

## ⚙️ Core Concepts

  * **Lexical Analysis:** Tokenizing input into a list of tokens based on operators, quotes, and spaces.
  * **Parsing:** Building a command and redirection structure from the token list.
  * **Expansion:** Handling environment variables and wildcards.
  * **Execution:** Executing commands, including built-ins and external programs, with support for pipes and redirections.
  * **Signals:** Managing signals for interactive and non-interactive modes.

-----

For complete details, refer to the subject file:
📄 [`en.subject.pdf`](https://github.com/Redadaghouj/42-minishell_1337/blob/main/subject/en.subject.pdf)
