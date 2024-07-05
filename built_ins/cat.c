/* #include <unistd.h> */
/* #include <fcntl.h> */
#include "get_next_line.h" 

int main(int ac, char **av)
{
	int i;
	int fd;
	char *line;
 
	if (ac != 2)
		return (1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1 || fd == 0)
		return (1);
	while (get_next_line(fd) != NULL)
	{
		line = get_next_line(fd);
		i = 0;
		while (line[i] != '\0')
		{
			write(1, &line[i], 1);
			i++;
		}
	}
	return (close(fd), 0);
}

