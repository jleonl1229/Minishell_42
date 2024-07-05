#include <unistd.h>

void noendln(int ac, char **av, int *i, int *ii)
{
	(*i)++;
	while (*i < ac)
	{
		(*ii) = 0;
		while (av[(*i)][(*ii)])
		{
			write(1, &av[(*i)][(*ii)], 1);
			(*ii)++;
		}
		if (*i + 1 != ac)
			write(1, " ", 1);
		(*i)++;
	}
}

void normal(int ac, char **av, int *i, int *ii)
{
	while (*i < ac)
	{
		(*ii) = 0;
		while (av[(*i)][(*ii)])
		{
			write(1, &av[(*i)][(*ii)], 1);
			(*ii)++;
		}
		if (*i + 1 != ac)
			write(1, " ", 1);
		(*i)++;
	}
	write(1, "\n", 1);
}

int main(int ac, char **av)
{
	int i;
	int ii;

	i = 0;
	ii = 0;
	i++;
	if (av[1][0] == '-' && av[1][1] == 'n' && av[1][2] == '\0')
		noendln(ac, av, &i, &ii);
	else
		normal(ac, av, &i, &ii);
	return (0);
}
