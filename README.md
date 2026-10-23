*This project has been created as part of the 42 curriculum by mibaboul.*

# Get Next Line

## Description

**Get Next Line (GNL)** is a C programming project from the 42 curriculum. Its goal is to implement a function that reads and returns one line at a time from a file descriptor.

```c
char *get_next_line(int fd);
```

Repeated calls retrieve successive lines without losing data that has already been read. A returned line includes its terminating newline (`\n`) when present. If the file ends without a final newline, the last line is returned as-is. The function returns `NULL` when there is nothing left to read or when an error occurs.

The project focuses on file descriptors, `read()`, dynamic memory allocation, and **static variables**. The mandatory implementation uses a persistent character buffer (often called a *stash*) to retain unread characters between calls.

## Instructions

### Files

The mandatory part uses the following files at the repository root:

- `get_next_line.c`
- `get_next_line_utils.c`
- `get_next_line.h`

### Compilation

Compile the source files alongside a test program containing a `main()` function:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c test.c -o gnl_test
./gnl_test
```

Replace `test.c` with your own test program. `BUFFER_SIZE` determines the maximum number of bytes requested per `read()` call. Test several values, including `1`, `42`, and large sizes. The project must also compile without `-D BUFFER_SIZE=...`; the header should define a default value in that case.

`get_next_line()` does not open or close files itself: the caller supplies a valid file descriptor and is responsible for closing it when appropriate. The caller must also `free()` each non-`NULL` line returned by the function.

### Expected behavior

For a text file containing `Hello\nWorld\nLast line` (with no newline after `Last line`), successive calls return:

1. `"Hello\n"`
2. `"World\n"`
3. `"Last line"`
4. `NULL`

The function is also intended to work with standard input. Reading a binary file, or modifying an associated file between calls before the reading reaches EOF, has undefined behavior under the project subject.

## Algorithm and Design Choices

This implementation follows a **dynamic string accumulation** approach rather than a linked list. A local `static char *stash` preserves data between calls to `get_next_line()`; this is necessary because a single `read()` may stop in the middle of a line or read characters belonging to a following line.

The algorithm is organized as follows:

1. **Validate the inputs.** Reject invalid file descriptors and non-positive buffer sizes.
2. **Accumulate data.** Check whether the stash already contains a newline. If not, read up to `BUFFER_SIZE` bytes into a temporary buffer. Use the actual number of bytes returned by `read()` and append the data to the stash.
3. **Stop reading at the right moment.** Stop when the stash contains a newline, when `read()` returns `0` (end of file), or when an error occurs. The function does not intentionally read the whole file before returning its first line.
4. **Extract one line.** Determine the length of the first line, including its newline if present. Allocate a separate string and copy only that line into it.
5. **Preserve the remainder.** Copy any characters after the extracted line into a new stash for the next call. If no characters remain, clear the stash.
6. **Manage ownership.** Release old temporary allocations and the previous stash when replacing them. The returned line remains owned by the caller. Handle allocation and reading errors without leaving inaccessible allocations.

### Why this approach?

A dynamically allocated character string is straightforward to manipulate with small helper functions for length calculation, copying, newline detection, and joining. It also makes the role of the static variable clear: **remember bytes already read but not yet returned**.

The trade-off is that repeated string concatenation may allocate and copy data multiple times, especially for very long lines with a small `BUFFER_SIZE`. For this introductory project, the approach prioritizes a clear separation of responsibilities and explicit memory management.

### Helper functions

The implementation is divided into small operations, string length and copying helpers, string concatenation (`my_strjoin`), extraction of the current line (`extract_line`), extraction of unread data (`extract_rest`), and reading into the persistent stash (`read_to_stash`). Exact placement of helpers depends on the final source organization.

## Resources

- [Linux manual: read(2)](https://man7.org/linux/man-pages/man2/read.2.html) — file-descriptor reading and return values.
- [Linux manual: malloc(3)](https://man7.org/linux/man-pages/man3/malloc.3.html) — dynamic allocation and freeing memory.
- [cppreference: storage duration](https://en.cppreference.com/w/c/language/storage_duration) — static storage duration in C.
- [42 Norm](https://github.com/42School/norminette) — C formatting and coding rules used for evaluation.
- **Get Next Line subject, version 14.3** — project specifications, restrictions, and evaluation requirements.

### AI usage

AI was used as a learning aid to review C concepts, including static variables, pointers, `read()`, buffer management, and dynamic allocation. It also helped review intermediate implementations, identify possible memory errors and edge cases, and discuss algorithm design and testing strategies. The project code was developed iteratively by the student.

## Testing Considerations

Useful checks include empty files, files with and without a final newline, consecutive newlines, very long lines, different `BUFFER_SIZE` values, standard input, invalid file descriptors, and allocation or read failures. Memory-management checks are especially important for detecting leaks, double frees, and invalid accesses.