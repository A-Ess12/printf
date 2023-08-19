#include <stdarg.h>
#include <unistd.h>

int _printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    int printed_chars = 0;

    for (int i = 0; format[i] != '\0'; i++)
    {
        if (format[i] != '%')
        {
            write(1, &format[i], 1);
            printed_chars++;
        }
        else
        {
            i++;  // Move past the '%'

            if (format[i] == 'c')
            {
                char c = va_arg(args, int);
                write(1, &c, 1);
                printed_chars++;
            }
            else if (format[i] == 's')
            {
                char *s = va_arg(args, char*);
                for (int j = 0; s[j] != '\0'; j++)
                {
                    write(1, &s[j], 1);
                    printed_chars++;
                }
            }
            else if (format[i] == '%')
            {
                write(1, &format[i], 1);
                printed_chars++;
            }
        }
    }

    va_end(args);

    return printed_chars;
}

int main()
{
    _printf("Hello, %c! This is a %s\n", 'W', "test");
    return 0;
}
