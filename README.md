# CommandLineInterpreter

A lightweight and extensible command-line interpreter written in C++.  
It supports UNIX-like commands, option parsing, input/output redirection, pipelining, and custom exception handling.

## Table of Contents

- [Commands](#commands)
- [Redirection](#redirection)
- [Pipeline](#pipeline)
- [Exceptions](#exceptions)

---

## Commands

| **Command** | **Description** |
|-------------|-----------------|
| [**echo**](#echo) | Prints the specified text to the console. Often used for displaying messages, debugging, or confirming input/output. |
| [**prompt**](#prompt) | Changes the current shell prompt text to a custom value, allowing users to personalize or differentiate command-line sessions. |
| [**time**](#time) | Displays the current system time in HH:MM:SS format, useful for tracking when certain commands are run. |
| [**date**](#date) | Shows the current date in a standardized YYYY-MM-DD format, helping with logs, timestamps, and schedule tracking. |
| [**touch**](#touch) | Creates an empty file with the specified name. If the file exists, it updates its last modification time without changing the contents. |
| [**truncate**](#truncate) | Empties an existing file by removing all its content, leaving an empty file with the same name intact. |
| [**rm**](#rm) | Permanently deletes the specified file from the file system. This action is irreversible within the command environment. |
| [**wc**](#wc) | Counts lines, words, or characters in a file. Supports options for flexible statistics and quick content analysis. |
| [**tr**](#tr) | Translates (replaces) or deletes characters in a given input string. Useful for simple character transformations or filtering. |
| [**head**](#head) | Outputs the first few lines of a file, with an optional parameter to control the number of lines shown. Helpful for previewing large files. |
| [**batch**](#batch) | Executes a sequence of commands stored in a file. Each line in the file is treated as an individual command and run in order. |
