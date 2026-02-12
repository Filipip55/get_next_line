*This project has been created as part of the 42 curriculum by icoman.*
# get_next_line - Reading a Line from a File Descriptor

## Description
**get_next_line** is a project from the 42 curriculum that challenges students to write a function capable of reading a line from a file descriptor, one line at a time. This project introduces the concept of static variables and file I/O operations, deepening understanding of memory management and buffer handling.

The function must work efficiently with different buffer sizes and handle multiple file descriptors simultaneously

## Project Content

### Main Function
| Function | Prototype | Description |
| :--- | :--- | :--- |
| `get_next_line` | `char *get_next_line(int fd)` | Reads and returns a line from a file descriptor. |

### Return Values
- **Line read**: Returns the line including the terminating `\n` character (if present)
- **End of file**: Returns `NULL` when there's nothing left to read
- **Error**: Returns `NULL` in case of an error

---

## Implementation Details

### Core Functions

| Function | Description |
| :--- | :--- |
| `get_next_line` | Main function that orchestrates reading, extraction, and cleanup. |
| `read_and_save` | Reads from file descriptor and accumulates data in the stash. |
| `strjoin_and_free` | Concatenates stash and buffer, freeing the old stash. |
| `extract_line` | Extracts a complete line from the stash. |
| `update_buffer` | Updates the stash by removing the extracted line. |

### Helper Functions

| Function | Description |
| :--- | :--- |
| `lst_new_node` | Creates a new node for the linked list. |
| `get_node_by_fd` | Finds or creates a node for the given file descriptor. |
| `remove_node` | Removes and frees a node when EOF is reached. |
| `search_newline` | Searches for the first newline character in a string. |
| `ft_strlen` | Calculates the length of a string. |

### Data Structure

This implementation uses a linked list to handle multiple file descriptors:

```c
typedef struct s_list
{
    int             fd;        // File descriptor
    char            *content;  // Stash (accumulated data)
    struct s_list   *next;     // Pointer to next node
}   t_list;
```

---

## How It Works

### Algorithm Flow

1. **Validation**: Checks if fd is valid and BUFFER_SIZE is positive
2. **Node Management**: Finds or creates a node for the given file descriptor
3. **Reading**: Reads from fd in chunks of BUFFER_SIZE until a newline is found or EOF
4. **Accumulation**: Concatenates read data into the stash using `strjoin_and_free`
5. **Extraction**: Extracts a complete line (up to and including `\n`) from the stash
6. **Cleanup**: Updates the stash to remove the extracted line
7. **Memory Management**: Removes the node if stash is empty (EOF reached)



## Requirements
* `gcc` compiler

## Installation

You can compile manually with a custom `BUFFER_SIZE`:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl
```

### Usage

Include `get_next_line_bonus.h` in your program:

```c
#include "get_next_line_bonus.h"

int main(void)
{
    ...
}
```

Compile with:
```bash
gcc -D BUFFER_SIZE=42 main.c get_next_line_bonus.c get_next_line_utils_bonus.c
```


---

## Project Structure

```
get_next_line/
├── get_next_line.c        # Main implementation
├── get_next_line_utils.c  # Helper functions
└── get_next_line.h        # Project header
```

---

## Technical Details

### BUFFER_SIZE
The buffer size can be defined at compilation time:
- Default value: `42`
- Can be any positive integer
- Affects memory usage and number of system calls
- The function works correctly with any buffer size (1, 42, 9999999)

### Memory Management
- Each line returned is dynamically allocated
- **Caller must free** the returned line
- Automatic cleanup when EOF is reached by removing its respective node
- No memory leaks even with large files or multiple descriptors

### Edge Cases Handled
- **Empty files**: Returns `NULL` immediately
- **Files without `\n`**: Returns the last line without newline character
- **Large lines**: Handles lines longer than `BUFFER_SIZE`
- **Binary files**: Works with any file content
- **Invalid fd**: Returns `NULL` for negative file descriptors
- **Read errors**: Proper error handling for failed read operations
- **Multiple fd**: Handles reading from different files simultaneously
- **EOF**: Automatically removes nodes when EOF is reached

---

## Multiple File Descriptors (Bonus)

The implementation uses a linked list where each node represents a buffer for a specific file descriptor:

```c
int fd1 = open("file1.txt", O_RDONLY);
int fd2 = open("file2.txt", O_RDONLY);
int fd3 = open("file3.txt", O_RDONLY);

line = get_next_line(fd1);  // Read from file1
line = get_next_line(fd2);  // Read from file2
line = get_next_line(fd3);  // Read from file3
line = get_next_line(fd1);  // Continue reading file1
```

Each file descriptor maintains its own:
- Buffer content (stash)
- Reading position
- State between calls

---



## Resources

- **Man pages**: `man read`, `man open`, `man close`
- **GeeksforGeeks**: [File I/O in C](https://www.geeksforgeeks.org/c/input-output-system-calls-c-create-open-close-read-write/)
- **GeeksforGeeks**: [Static Variables in C](https://www.geeksforgeeks.org/c/static-variables-in-c/)
- **GeeksforGeeks**: [Linked Lists in C](https://www.geeksforgeeks.org/c/linked-list-in-c/)

---