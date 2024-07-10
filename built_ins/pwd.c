#include <stdio.h>
#include <limits.h>

int main(void)
{
	char cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) != NULL)
		printf("%s\n", cwd);
	else
		return (printf("Error"), 1);
	return (0);
}
