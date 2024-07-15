#include "../minishell.h"



void skip_spaces(char *str, int *index) {
    while (str[*index] != '\0' && (str[*index] == 32 || (str[*index]) == 9))
		(*index)++;
}

void skip_quotes(char *str, int *index) 
{
    char quote_char;
	
	quote_char = str[*index];
    (*index)++;
    while (str[*index] != '\0' && str[*index] != quote_char)
        (*index)++;
    if (str[*index] == quote_char) //skip closing quote
        (*index)++;
}

/*
Validates that special characters are not separated by spaces or tabs (except for '| >' and '| <')
Example: 'cat | | cat' results in a syntax error
*/
int	space_and_chars(char *line)
{
	int	i;
	const char *special_chars;
	char c;
	
	special_chars = "<>|";
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == 39 || line[i] == 34) //double or single quotes
			skip_quotes(line, &i);
		if (strchr(special_chars, line[i]) && line[i + 1] == ' ')
		{
			c = line[i];
			i++;
			skip_spaces(line, &i);
			if (strchr(special_chars, line[i]) 
			&& !(c == '|' && (line[i] == '<' || line[i] == '>'))) // "| <" and "| >" doesn't throw syntax error
			{
				printf("bash: syntax error near unexpected token '%c'\n", line[i]);
				return (1);
			}
		}
		if (line[i]) //I think we can get rid of this condition
			i++;
	}
	return (0);
}