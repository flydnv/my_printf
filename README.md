# Welcome to My Printf
***

## Task
The goal of this project is to re-implement the standard C library `printf` function (`int my_printf(char * restrict format, ...);`) from scratch without relying on any built-in `printf`-family functions.

The core challenge lies in managing an unknown number of arguments of varying types using variadic macros (`<stdarg.h>`), parsing format strings character by character, and converting integers and memory addresses into ASCII characters across multiple numeral systems (decimal, octal, and hexadecimal) using only the low-level `write` system call—while accurately tracking the total number of printed characters and handling edge cases such as `NULL` pointers, `NULL` strings, and `INT_MIN`.

## Description
The solution is structured modularly inside `my_printf.c` with separate helper functions for each formatting responsibility:

* **Core Parser (`my_printf`)**: Validates the `format` string, initializes `va_list` via `va_start`, iterates through each character, delegates `%` format specifiers to `handle_specifier`, prints literal characters directly, and returns the exact character count after calling `va_end`.
* **Specifier Router (`handle_specifier`)**: Extracts the corresponding argument with `va_arg` and dispatches it to the appropriate output helper for `%c`, `%s`, `%d`, `%u`, `%o`, `%x`, `%p`, and `%%`.
* **Character & String Output (`my_putchar`, `my_putstr`)**: Uses `write(1, &c, 1)` to output individual characters and strings, printing `(null)` safely when a `NULL` `char *` is passed.
* **Numeric & Base Conversion (`my_put_unsigned`, `my_put_signed`, `my_put_octal`, `my_put_hex`)**: Uses recursion to break numbers down from left to right. `my_put_signed` casts `int` to `long` to safely handle `INT_MIN` (`-2147483648`), while `my_put_hex` accepts a character set parameter to render uppercase hex digits for `%x` and lowercase hex digits for `%p`.
* **Pointer Formatting (`my_put_ptr`)**: Casts `void *` addresses to `unsigned long`, prefixes non-null addresses with `0x`, and outputs `(nil)` for `NULL` pointers.

## Installation
Compile `my_printf.c` alongside your test file containing `main()` using `gcc` with strict warning flags, or build via `Makefile` if configured:

```bash
gcc -Wall -Wextra -Werror my_printf.c main.c -o my_printf
```

If using a `Makefile`:
```bash
make re
```

## Usage
Include the `my_printf` prototype in your C source file and call it with any supported format specifiers (`%c`, `%s`, `%d`, `%u`, `%o`, `%x`, `%p`, `%%`):

```c
#include <stddef.h>

int my_printf(char * restrict format, ...);

int main(void)
{
    int num = 42;

    my_printf("Char: %c | String: %s\n", 'A', "Hello");
    my_printf("Signed: %d | Unsigned: %u\n", -42, 42);
    my_printf("Octal: %o | Hex: %x\n", 100, 255);
    my_printf("Pointer: %p | Null: %p | Percent: %%\n", &num, NULL);
    return (0);
}
```

Compile and run the executable:
```bash
./my_printf
```

### The Core Team
* Qwasar SV Student

<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>