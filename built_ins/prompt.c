#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	while (1)
	{
		readline(0, "$ ");
	}
	return (0);
}
