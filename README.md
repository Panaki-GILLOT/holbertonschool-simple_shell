# Simple Shell — hsh

A simple UNIX command line interpreter written in C, reproducing the basic behavior of `/bin/sh`.

---

## Description

`hsh` is a simple shell written in C as part of the Holberton School curriculum. It reads commands from standard input (interactive or non-interactive), searches for them in the `PATH`, and executes them using `fork()` and `execve()`.

---

## Features

- Interactive and non-interactive mode
- Command execution with full path (`/bin/ls`) or via `PATH` resolution (`ls`)
- Error handling mimicking `/bin/sh`
- Built-in: `exit`, `env`
- Handles `EOF` (Ctrl+D)
- No memory leaks

---

## Requirements

- Ubuntu 20.04 LTS
- GCC with flags: `-Wall -Werror -Wextra -pedantic -std=gnu89`

---

## Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

---

## Usage

### Interactive mode

```bash
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($) ls
hsh main.c shell.c
($) exit
$
```

### Non-interactive mode

```bash
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c

$ cat commands.txt | ./hsh
hsh main.c shell.c
```

---

## Error handling

The shell prints errors using the program name as it was called:

```bash
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found

$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
```

---

## File structure

| File | Description |
|------|-------------|
| `main.c` | Entry point — main loop |
| `shell.c` | Core shell functions |
| `shell.h` | Header file — prototypes and includes |
| `AUTHORS` | List of contributors |
| `man_1_simple_shell` | Manual page |

---

## Authors

See [AUTHORS](./AUTHORS)

---

## License

This project is part of the Holberton School curriculum.