// Assignment name  : ft_printf
// Expected files   : ft_printf.c
// Allowed functions: malloc, free, write, va_start, va_arg, va_copy, va_end
// --------------------------------------------------------------------------------

// Write a function named `ft_printf` that will mimic the real printf with the following constraints:

// - It will manage only the following conversions: s,d and x
// - It will manage the minimum field width. (we will never test with a field with of 0)
// - It will manage only the precison flag `.`.

// Your function must be declared as follows:

// int ft_printf(const char *, ... );

// Before you start we advise you to read the `man 3 printf` and the `man va_arg`.
// To test your program compare your results with the true printf.

// % [width] [.] [precision] [specifier]

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_info
{
	int count;
	int width;
	int point;
	int prec;
	int spec;
}				t_info;


void	ft_putchar(t_info *info, char c)
{
	write(1, &c, 1);
	info->count++;
}

int ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int ft_countnumbers(char *s)
{
	int len = 0;
	while (ft_isdigit(*s))
	{
		s++;
		len++;
	}
	return (len);
}

int ft_inset(char c, char *s)
{
	while (*s)
	{
		if (c == *s)
			return (1);
		s++;
	}
	return (0);
}

int ft_atoi(char *s)
{
	int i = 0;
	int num = 0;

	while (ft_isdigit(s[i]))
	{
		num = num * 10 + s[i] - '0';
		i++;
	}
	return (num);
}

void ft_putnbr(t_info *info, int num)
{
	if (num > 9)
		ft_putnbr(info, num / 10);
	ft_putchar(info, (num % 10) + '0');
}

void ft_puthexnbr(t_info *info, unsigned int num)
{
	char basestr[17] = "0123456789abcdef";
	if (num > 16)
		ft_puthexnbr(info, num / 16);
	ft_putchar(info, basestr[num % 16]);
}

// % [width] [.] [precision] [specifier]

char *ft_parse(t_info *info, char *s)
{
	info->width = 0;
	info->point = 0;
	info->prec = 0;
	info->spec = 0;
	s++;

	if (ft_isdigit(*s))
	{
		info->width = ft_atoi(s);
		s = s + ft_countnumbers(s);
	}
	if (*s == '.')
	{
		info->point = 1;
		s++;
		if (ft_isdigit(*s))
		{
			info->prec = ft_atoi(s);
			s = s + ft_countnumbers(s);
		}
	}
	if (ft_inset(*s, "sdx"))
	{
		info->spec = *s;
		s++;
	}

	// printf("width: %d\n", info->width);
	// printf("point: %d\n", info->point);
	// printf("prec: %d\n", info->prec);
	// printf("spec: %c\n", info->spec);
	return (s);
}

void ft_putstrlen(t_info *info, char *s, int len)
{
	int i = 0;

	while (s[i] && i < len)
	{
		ft_putchar(info, s[i]);
		i++;
	}
}

int ft_strlen(char *s)
{
	int len = 0;
	while (*s)
	{
		len++;
		s++;
	}
	return (len);
}

int ft_numlen(int num)
{
	int len = 1;
	while (num > 9)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

int ft_hexlen(unsigned int num)
{
	int len = 1;
	int base = 16;
	unsigned exp = 1;

	while (num / base / exp)
	{
		exp *= base;
		len++;
	}
	return (len);
}

void ft_putpadding(t_info *info, char c, int amount)
{
	int i = 0;
	while (i < amount)
	{
		ft_putchar(info, c);
		i++;
	}
}

void ft_print_string(t_info *info, char *s)
{
	int len;

	if (!s)
		s = "(null)";
	len = ft_strlen(s);
	if (info->point && info->prec < len)
		len = info->prec;
	ft_putpadding(info, ' ', info->width - len);
	ft_putstrlen(info, s, len);
}

void ft_print_neg_int(t_info *info, int num)
{
	int len;
	int len_exprec;

	if (num == -2147483648)
	{
		ft_putstrlen(info, "-2147483648", 11);
		return ;
	}
	num = num * -1;
	len = ft_numlen(num);
	len_exprec = len;
	if (info->prec > len)
		len = info->prec;
	ft_putpadding(info, ' ', info->width - len - 1);
	ft_putchar(info, '-');
	ft_putpadding(info, '0', info->prec - len_exprec);
	ft_putnbr(info, num);
}

void ft_print_int(t_info *info, int num)
{
	int len;
	int len_exprec;

	if (num < 0)
	{
		ft_print_neg_int(info, num);
		return ;
	}
	if (num == 0)
	{
		if (info->point && info->prec == 0)
		{
			ft_putpadding(info, ' ', info->width);
			return ;
		}
	}
	len = ft_numlen(num);
	len_exprec = len;
	if (info->prec > len)
		len = info->prec;
	ft_putpadding(info, ' ', info->width - len);
	ft_putpadding(info, '0', info->prec - len_exprec);
	ft_putnbr(info, num);
}

void ft_print_hex(t_info *info, unsigned num)
{
	int len;
	int len_exprec;

	len = ft_hexlen(num);
	len_exprec = len;
	if (info->prec > len)
		len = info->prec;
	ft_putpadding(info, ' ', info->width - len);
	ft_putpadding(info, '0', info->prec - len_exprec);
	ft_puthexnbr(info, num);
}

void ft_printvar(t_info *info, va_list args)
{
	if (info->spec == 's')
	{
		char *s;
		s = va_arg(args, char *);
		ft_print_string(info, s);
	}
	else if (info->spec == 'd')
	{
		int num;
		num = va_arg(args, int);
		ft_print_int(info, num);
	}
	else if (info->spec == 'x')
	{
		unsigned nbr;
		nbr = va_arg(args, unsigned);
		
		ft_print_hex(info, nbr);
	}
}

int ft_printf(const char *s, ... )
{
	t_info info;
	va_list args;

	va_start(args, (char *)s);
	info.count = 0;

	while (s && *s)
	{
		if (*s == '%')
		{
			s = ft_parse(&info, (char *)s);
			ft_printvar(&info, args);
		}
		else if (*s)
		{
			ft_putchar(&info, *s);
			s++;
		}
	}
	va_end(args);
	return (info.count);
}

int main (void)
{
	if (TEST == 1) // test s
	{
		printf("---- Return: %d\n", ft_printf("test: %s", "hallo"));
		printf("---- Return: %d\n\n",  printf("test: %s", "hallo"));

		printf("---- Return: %d\n", ft_printf("%3s", "hallo"));
		printf("---- Return: %d\n\n",  printf("%3s", "hallo"));

		printf("---- Return: %d\n", ft_printf("%5s", "hallo"));
		printf("---- Return: %d\n\n",  printf("%5s", "hallo"));

		printf("---- Return: %d\n", ft_printf("%20s", "hallo"));
		printf("---- Return: %d\n\n",  printf("%20s", "hallo"));

		printf("---- Return: %d\n", ft_printf("%.1s", "hallo"));
		printf("---- Return: %d\n\n",  printf("%.1s", "hallo"));

		printf("---- Return: %d\n", ft_printf("%10.1s", "hallo"));
		printf("---- Return: %d\n\n",  printf("%10.1s", "hallo"));

		printf("---- Return: %d\n", ft_printf("%.5s", "hallo"));
		printf("---- Return: %d\n\n",  printf("%.5s", "hallo"));

		printf("---- Return: %d\n", ft_printf("%.s", "hallo"));
		printf("---- Return: %d\n\n",  printf("%.s", "hallo"));

		printf("---- Return: %d\n", ft_printf("%s%s", "hello", "world"));
		printf("---- Return: %d\n\n",  printf("%s%s", "hello", "world"));


		// printf("---- Return: %d\n", ft_printf("%s", 0));
		// printf("---- Return: %d\n\n",  printf("%s", 0));

		// printf("---- Return: %d\n", ft_printf("%10.2s", 0));
		// printf("---- Return: %d\n\n",  printf("%10.2s", 0));
	}
	if (TEST == 2) // test d
	{
		printf("---- Return: %d\n", ft_printf("test: %d", 12345));
		printf("---- Return: %d\n\n",  printf("test: %d", 12345));

		printf("---- Return: %d\n", ft_printf("%13d", 1234));
		printf("---- Return: %d\n\n",  printf("%13d", 1234));

		printf("---- Return: %d\n", ft_printf("%13.8d", 1234));
		printf("---- Return: %d\n\n",  printf("%13.8d", 1234));

		printf("---- Return: %d\n", ft_printf("test: %d", -12345));
		printf("---- Return: %d\n\n",  printf("test: %d", -12345));

		printf("---- Return: %d\n", ft_printf("%13d", -1234));
		printf("---- Return: %d\n\n",  printf("%13d", -1234));

		printf("---- Return: %d\n", ft_printf("%13.8d", -1234));
		printf("---- Return: %d\n\n",  printf("%13.8d", -1234));

		printf("---- Return: %d\n", ft_printf("%13.0d", -1234));
		printf("---- Return: %d\n\n",  printf("%13.0d", -1234));

		printf("---- Return: %d\n", ft_printf("%d", 2147483647));
		printf("---- Return: %d\n\n",  printf("%d", 2147483647));

		printf("---- Return: %d\n", ft_printf("%d", -2147483648));
		printf("---- Return: %d\n\n",  printf("%ld", -2147483648));

		printf("---- Return: %d\n", ft_printf("%13d", 0));
		printf("---- Return: %d\n\n",  printf("%13d", 0));

		printf("---- Return: %d\n", ft_printf("%13.8d", 0));
		printf("---- Return: %d\n\n",  printf("%13.8d", 0));

		printf("---- Return: %d\n", ft_printf("%13.0d", 0));
		printf("---- Return: %d\n\n",  printf("%13.0d", 0));
	}
	if (TEST == 3) // test x
	{
		printf("---- Return: %d\n", ft_printf("test: %x", 12345));
		printf("---- Return: %d\n\n",  printf("test: %x", 12345));

		printf("---- Return: %d\n", ft_printf("%13x", 1234));
		printf("---- Return: %d\n\n",  printf("%13x", 1234));

		printf("---- Return: %d\n", ft_printf("%13.8x", 1234));
		printf("---- Return: %d\n\n",  printf("%13.8x", 1234));

		printf("---- Return: %d\n", ft_printf("test: %x", -12345));
		printf("---- Return: %d\n\n",  printf("test: %x", -12345));

		printf("---- Return: %d\n", ft_printf("%13x", -1234));
		printf("---- Return: %d\n\n",  printf("%13x", -1234));

		printf("---- Return: %d\n", ft_printf("%13.8x", -1234));
		printf("---- Return: %d\n\n",  printf("%13.8x", -1234));

		printf("---- Return: %d\n", ft_printf("%13.0x", -1234));
		printf("---- Return: %d\n\n",  printf("%13.0x", -1234));

		printf("---- Return: %d\n", ft_printf("%.20x", -1234));
		printf("---- Return: %d\n\n",  printf("%.20x", -1234));
	}
}