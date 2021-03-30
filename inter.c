// en
// Write a program that takes two strings and displays, without doubles, the
// characters that appear in both strings, in the order they appear in the first
// one.

// The display will be followed by a \n.

// If the number of arguments is not 2, the program displays \n.

#include <unistd.h>

int ft_inset(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return 1;
		set++;
	}
	return (0);
}

void ft_putchar(char c)
{
	write(1, &c, 1);
}

void ft_fillzero(char *s)
{
	while (*s)
	{
		*s = '\0';
		s++;
	}
}

int main (int argc, char *argv[])
{
	if (argc == 3)
	{
		char *s1;
		char *s2;
		char printed[200];
		printed[199] = '\0';
		ft_fillzero(printed);

		s1 = argv[1];
		s2 = argv[2];
		int i = 0;
		int j = 0;
		while (s1[i])
		{
			if (ft_inset(s1[i], s2) && (!(ft_inset(s1[i], printed))))
			{
				ft_putchar(s1[i]);
				printed[j] = s1[i];
				j++;
			}
			i++;
		}
	}
	ft_putchar('\n');
}