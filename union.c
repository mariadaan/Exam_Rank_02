// Assignment name  : union
// Expected files   : union.c
// Allowed functions: write
// --------------------------------------------------------------------------------
// en
// Write a program that takes two strings and displays, without doubles, the
// characters that appear in either one of the strings.

// The display will be in the order characters appear in the command line, and
// will be followed by a \n.

// If the number of arguments is not 2, the program displays \n.
// ----------------------------------------------------------------------------------

// Example:

// $>./union zpadinton "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
// zpadintoqefwjy$
// $>./union ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
// df6vewg4thras$
// $>./union "rien" "cette phrase ne cache rien" | cat -e
// rienct phas$
// $>./union | cat -e
// $
// $>
// $>./union "rien" | cat -e
// $
// $>

#include <unistd.h>

void ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_inset(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
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
	if (argc != 3)
	{
		ft_putchar('\n');
		return (0);
	}

	char alphabet[201];
	alphabet[200] = '\0';
	ft_fillzero(alphabet);
	char *s1;
	char *s2;

	s1 = argv[1];
	s2 = argv[2];

	int i = 0;
	int j = 0;
	while (s1[i])
	{
		if (!(ft_inset(s1[i], alphabet)))
		{
			ft_putchar(s1[i]);
			alphabet[j] = s1[i];
			j++;
		}
		i++;
	}
	i = 0;
	while (s2[i])
	{
		if (!(ft_inset(s2[i], alphabet)))
		{
			ft_putchar(s2[i]);
			alphabet[j] = s2[i];
			j++;
		}
		i++;
	}
	ft_putchar('\n');
}