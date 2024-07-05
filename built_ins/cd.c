#include <unistd.h>
#include <stdio.h>

int main (int ac, char **av)
{
	if (ac == 1)
		chdir("~");
	else if (ac == 2)
	{
		if (chdir(av[1]) != -1)
			return (0); //Here the minishell should handle the directory changing, maybe it would work just like this with no more changes
		else
			return (printf("-bash: cd: %s: No such file or directory\n", av[1]), 1);
	}
	else if (ac > 2)
		return (write(1, "-bash: cd: too many arguments\n", 30), 1);
	return (0);
}
