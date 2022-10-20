#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(char *s)
{
	int len = 0;
	while (s && *s)
	{
		s++;
		len++;
	}
	return (len);
}

char *ft_join(char *s, char c)
{
	int len = ft_strlen(s);
	char *tmp = malloc(len + 2);
	int i = 0;
	while (i < len)
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[len] = c;
	tmp[len + 1] = '\0';
	free(s);
	return (tmp);
}

int get_next_line(char **line)
{
	int fd = 0;
	char buf[2];
	int ret = 1;
	
	*line = 0;
	while (ret)
	{
		ret = read(fd, buf, 1);
		if (ret == 0)
			return (0);
		else if (*buf != '\n' )
			*line = ft_join(*line, *buf);
		else if (!(*line))
		{
			*line = malloc(1);
			*line[0] = '\0';
			return (1);
		}
		else
			return (1);
	}
	return (0);
}

int main (void)
{
	char *line;
	int ret = 1;

	while (ret > 0)
	{
		ret = get_next_line(&line);
		printf("%d: %s\n", ret, line);
		free(line);
	}
}