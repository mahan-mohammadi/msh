# msh

A simple shell implementation written in C.

## Overview

`msh` is a Unix-like command shell project that implements basic shell functionality such as reading commands, executing programs, and handling user input.

The goal of this project is to understand how shells work internally, including:

- Process creation
- Command parsing
- Program execution
- System calls
- File descriptors

## Features

- Execute external commands
- Command parsing
- Process creation using `fork()`
- Program execution using `execvp()`
- Waiting for processes
- Basic shell loop

## Build

Clone the repository:

```bash
git clone https://github.com/mahan-mohammadi/msh.git
cd msh
