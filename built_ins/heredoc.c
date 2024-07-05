#include <unistd.h>

int main(void)
{
	char *prompt;

	while (1)
	{
		ft_printf("$ ");
		prompt = get_next_line(0);
		handleinput();	
	}
	return (0);
}
