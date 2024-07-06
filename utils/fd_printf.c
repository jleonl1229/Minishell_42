#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

void get_hex(int fd, unsigned long num, int *total)
{
	char *arr;
	char c;

	if (num > 15)
		get_hex(fd, num / 16, total);
	arr = "0123456789abcdef";
	c = arr[num % 16];
	*total += write(fd, &c, 1);
}

void get_int(int fd, int num, int *total)
{
	char c;

	if (num < 0)
	{
		*total += write(fd, "-", 1);
		num *= -1;
	}
	if (num > 9)
		get_int(fd, num / 10, total);
	c = num % 10 + '0';
	*total += write(fd, &c, 1);
}

void get_str(int fd, char *str, int *total)
{
	while (*str)
	{
		*total += write(fd, str, 1);
		str = str + 1;
	}
}

int fd_printf(int fd, char const *format, ...)
{
	va_list arg;
	int total;

	total = 0;
	va_start(arg, format);
	while (*format)
	{
		if (*format == '%')
		{
			if (*(format + 1) == 's' || *(format + 1) == 'd' || *(format + 1) == 'x' && *format)
			{
				format = format + 1;
				if (*format ==  's')
					get_str(fd, va_arg(arg, char *), &total);
				else if (*format == 'd')
					get_int(fd, va_arg(arg, int), &total);
				else if (*format == 'x')
					get_hex(fd, va_arg(arg, unsigned long), &total);
				format = format + 1;
			}
			else
				return (-1);
		}
		else
		{
			total += write(fd, format, 1);
			format = format + 1;
		}
	}
	va_end(arg);
	return (total);
}

/* void think(va_list *arg, int *total, char const *format, int fd) */
/* { */
/* 	format = format + 1; */
/* 	if (*format ==  's') */
/* 		get_str(fd, va_arg(*arg, char *), total); */
/* 	else if (*format == 'd') */
/* 		get_int(fd, va_arg(*arg, int), total); */
/* 	else if (*format == 'x') */
/* 		get_hex(fd, va_arg(*arg, unsigned long), total); */
/* 	format = format + 1; */
/* } */

/* int fd_printf(int fd, char const *format, ...) */
/* { */
/* 	va_list arg; */
/* 	int total; */

/* 	total = 0; */
/* 	va_start(arg, format); */
/* 	while (*format) */
/* 	{ */
/* 		if (*format == '%') */
/* 		{ */
/* 			if (*(format + 1) == 's' || *(format + 1) == 'd' || *(format + 1) == 'x' && *format) */
/* 			{ */
/* 				think(&arg, &total, format, fd); */
/* 			} */
/* 			else */
/* 				return (-1); */
/* 		} */
/* 		else */
/* 		{ */
/* 			total += write(fd, format, 1); */
/* 			format = format + 1; */
/* 		} */
/* 	} */
/* 	va_end(arg); */
/* 	return (total); */
/* } */

int main(void)
{
	int n = fd_printf(1, "%d", 150);
	printf("\n%x", n);
	return (0);
}
