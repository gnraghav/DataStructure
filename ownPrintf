#include <stdio.h>
#include <stdarg.h>  // Needed for va_list, va_start, and va_end

// Helper function to print an integer
void printInt(int num) {
    if (num == 0) {
        putchar('0');
        return;
    }

    if (num < 0) {
        putchar('-');
        num = -num;
    }

    char buffer[20];  // Temporary buffer to hold digits
    int i = 0;

    while (num > 0) {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    // Print the digits in reverse order
    for (int j = i - 1; j >= 0; j--) {
        putchar(buffer[j]);
    }
}

// Custom printf implementation
void my_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    const char *str = format;
    
    while (*str != '\0') {
        if (*str == '%') {
            str++;  // Move to the format specifier
            switch (*str) {
                case 'd': {
                    int num = va_arg(args, int);
                    printInt(num);  // Call helper to print the integer
                    break;
                }
                case 's': {
                    const char *s = va_arg(args, const char *);
                    while (*s != '\0') {
                        putchar(*s++);
                    }
                    break;
                }
                case 'c': {
                    char c = (char)va_arg(args, int);
                    putchar(c);
                    break;
                }
                default:
                    putchar('%');  // Print '%' for unknown specifiers
                    putchar(*str);
            }
        } else {
            putchar(*str);  // Print regular characters
        }
        str++;  // Move to the next character in the format string
    }

    va_end(args);
}

int main() {
    my_printf("Hello, %s! Your score is %d, and your grade is '%c'.\n", "Alice", 95, 'A');
    return 0;
}
