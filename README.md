# 🐚 Minishell
**As beautiful as a shell.**

## 📖 Overview
Minishell is a 1337/42 project where I built a simplified version of the Bash shell. This project is a deep dive into how an Operating System handles command execution, process lifecycles, and system-level communication.



## 🛠️ Features
My implementation mimics Bash behavior and includes:
* **Interactive Prompt:** Displays a prompt and waits for user input.
* **Command Execution:** Locates and executes binaries using the `PATH` variable.
* **Built-ins:** Re-coded standard commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
* **Redirections:** Handles `<`, `>`, `>>`, and the `<<` (heredoc) operators.
* **Pipes:** Implements pipelines (`|`) where the output of one command becomes the input of the next.
* **Environment Variables:** Full expansion of `$VAR` and `$?`.
* **Signal Handling:** Proper management of `Ctrl-C`, `Ctrl-D`, and `Ctrl-\`.

## 🏗️ Technical Challenges
### 1. The Parser (Lexer & Executor)
I built a robust tokenizer to handle quotes (`" "`, `' '`) and complex strings. The challenge was ensuring that the shell correctly distinguished between meta-characters (like `|`) and literal strings.

### 2. Process Management
Used `fork`, `waitpid`, and `execve` to manage child processes. I had to ensure that the parent shell remains active while child processes execute and that all file descriptors are properly closed to prevent leaks.



### 3. Redirections & Pipes
Managing the "plumbing" of the shell required a deep understanding of `pipe()`, `dup2()`, and file permissions to ensure data flows correctly between commands and files.

## 💻 How to Run
1. **Clone and Compile:**
   ```bash
   git clone [YOUR_REPO_LINK] && cd minishell
   make
