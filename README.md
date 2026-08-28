# Minishell 🐚

A **42 School** project that consists of building a small Unix shell inspired by `bash`.

The project was developed by a team of two. The work was divided into two main parts:

* **Parsing** — `abdejl`
* **Execution** — `brbaazi`

The goal of Minishell is to understand how a shell works internally, including command parsing, process management, pipes, redirections, environment variables, and signals.

---

## 📖 Overview

Minishell reads commands from the user, analyzes them, and executes them like a basic Unix shell.

The project covers important Unix concepts such as:

* Processes
* File descriptors
* Pipes
* Redirections
* Signals
* Environment variables
* Command execution
* Built-in commands
* Heredocs

---

## 👥 Team

### 🧩 Parsing — `abdejl`

Responsible for the parsing part of the project.

Main responsibilities:

* Lexing and tokenization
* Syntax validation
* Quote handling
* Pipe parsing
* Redirection parsing
* Environment variable expansion
* Command structure creation

GitHub: [abdejl](https://github.com/abdejl)

### ⚙️ Execution — `brbaazi`

Responsible for the execution part of the project.

Main responsibilities:

* Process creation with `fork()`
* Command execution with `execve()`
* Process synchronization with `waitpid()`
* Pipe management
* File descriptor management
* Input/output redirections
* Heredoc execution
* Built-in command execution
* Exit status management
* Signal handling
* `PATH` command lookup

GitHub: [brbaazi](https://github.com/brbaazi)

---

## ✨ Features

### Built-in Commands

Minishell supports:

```text
echo
cd
pwd
export
unset
env
exit
```

### Pipes

Multiple commands can be connected using pipes:

```bash
ls -l | grep ".c" | wc -l
```

The output of one command becomes the input of the next command.

### Redirections

Supported redirections:

```text
>
<
>>
```

Examples:

```bash
echo "Hello" > file.txt
cat < file.txt
echo "World" >> file.txt
```

### Heredoc

Minishell supports heredocs using `<<`:

```bash
cat << EOF
Hello
World
EOF
```

### Environment Variables

Environment variables can be expanded:

```bash
echo $USER
echo $HOME
echo $PATH
```

The special variable `$?` returns the exit status of the previous command:

```bash
echo $?
```

### Signals

Minishell handles the main shell signals:

| Signal   | Behavior                         |
| -------- | -------------------------------- |
| `Ctrl-C` | Displays a new prompt            |
| `Ctrl-D` | Exits the shell                  |
| `Ctrl-\` | Does nothing in interactive mode |

### Command History

Minishell uses the `readline` library to provide command history and interactive input.

---

## ⚙️ How It Works

The shell follows a pipeline from user input to command execution:

```text
                    User Input
                        │
                        ▼
                ┌──────────────┐
                │    Lexer     │
                │    Parser    │
                └──────┬───────┘
                       │
                       ▼
              Command Structures
                       │
                       ▼
                ┌──────────────┐
                │   Expansion  │
                └──────┬───────┘
                       │
                       ▼
                ┌──────────────┐
                │   Execution  │
                └──────┬───────┘
                       │
          ┌────────────┼────────────┐
          ▼            ▼            ▼
        Pipes      Redirections   Built-ins
          │            │            │
          └────────────┼────────────┘
                       ▼
                 Command Output
```

### Execution Flow

1. The user enters a command.
2. The parser creates a command structure.
3. Environment variables are expanded.
4. Pipes and redirections are prepared.
5. Processes are created with `fork()`.
6. File descriptors are configured with `dup2()`.
7. External commands are executed with `execve()`.
8. The parent process waits with `waitpid()`.
9. The final exit status is updated.

---

## 🧠 What We Learned

This project gave us a strong understanding of Unix systems and shell behavior.

### Parsing

* Tokenization
* Syntax analysis
* Quotes
* Environment expansion
* Command structures

### Execution

* Processes
* `fork()`
* `execve()`
* `waitpid()`
* `pipe()`
* `dup2()`
* `open()`
* File descriptors
* Signals
* Exit statuses

### Teamwork

The project also taught us how to divide a large project into different parts and connect the **parser** with the **executor**.

---

## 🛠️ Technologies

* C
* Unix / Linux
* Makefile
* Readline
* Unix System Calls
* Git / GitHub

---

## 📦 Installation

Clone the repository:

```bash
git clone <repository-url>
cd minishell
```

Compile the project:

```bash
make
```

Run Minishell:

```bash
./minishell
```

---

## 🧹 Make Commands

Compile:

```bash
make
```

Remove object files:

```bash
make clean
```

Remove object files and the executable:

```bash
make fclean
```

Recompile everything:

```bash
make re
```

---

## 🧪 Examples

### Simple command

```bash
minishell$ echo "Hello World"
Hello World
```

### Pipe

```bash
minishell$ ls | grep ".c"
```

### Redirection

```bash
minishell$ echo "Hello" > file.txt
minishell$ cat file.txt
Hello
```

### Append

```bash
minishell$ echo "World" >> file.txt
minishell$ cat file.txt
Hello
World
```

### Environment variable

```bash
minishell$ echo $HOME
/home/user
```

### Exit status

```bash
minishell$ ls
minishell$ echo $?
0
```

---

## 🎯 Project Objective

The main objective of Minishell is to understand how a Unix shell works internally.

Instead of using high-level shell functionality, we implemented the main mechanisms ourselves using C and Unix system calls.

This project helped us improve our understanding of:

**Parsing → Processes → File Descriptors → Pipes → Signals → Command Execution**

---

## 👨‍💻 Authors

| Part      | GitHub                                |
| --------- | ------------------------------------- |
| Parsing   | [abdejl](https://github.com/abdejl)   |
| Execution | [brbaazi](https://github.com/brbaazi) |

**42 School — Minishell**
