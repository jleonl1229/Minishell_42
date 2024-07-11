#include "../minishell.h"

/*
checks if string is only space. 
returns 0 if non-space char found
*/
int	is_space(char *line)
{
	int	is_space;

	if (line == NULL || *line == '\0')
		return (0);
	is_space = 1;
	while (*line)
	{
		if (!((9 <= *line && *line <= 13) || *line == 32)) 
		{
			is_space = 0;
			break ;
		}
		line++;
	}
	return (is_space);
}