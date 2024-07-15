#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*int is_open_quotes (char *line)
{
	int	single_q;
	int	double_q;

	single_q = 0;
	double_q = 0;
	while (*line != '\0')
	{
		if (*line == 34 && single_q == 0)
			double_q = !double_q ;
		else if (*line == 39 && double_q == 0)
			single_q = !single_q;
		line++;
	}
	if (single_q ||double_q)
	{
		//printf("syntax error: unclosed quotes\n");
		return 1;
	}
	return 0;
}

int main() {
    char input[100];  // Assuming a maximum input length of 100 characters

    printf("Enter test strings (one per line):\n");

    while (fgets(input, sizeof(input), stdin)) {
        // Remove newline character if present
        input[strcspn(input, "\n")] = '\0';

        // Check if quotes are open in the input string
        printf("Test: %s: %s\n", input, is_open_quotes(input) ? "Open" : "Closed");
    }

    return 0;
}*/

#include <stdio.h>
#include <stdbool.h>


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

bool	validate_syntax(char *line)
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
				return (0);
			}
		}
		if (line[i])
			i++;
	}
	return (1);
}

int main() {
    char input[100];  // Assuming a maximum input length of 100 characters

    printf("Enter test strings (one per line):\n");

    while (fgets(input, sizeof(input), stdin)) {
        // Remove newline character if present
        input[strcspn(input, "\n")] = '\0';

        // Check if the syntax is valid
        printf("Test: %s: %s\n", input, validate_syntax(input) ? "OK" : "syntax Error");
    }

    return 0;
}


/*int main() {
    const char *test_input1 = "test | test";
    const char *test_input2 = "test |   | test";
    const char *test_input3 = "echo \"hello < <\"";

    if (validate_syntax(test_input1)) {
        printf("'%s' is valid\n", test_input1);
    } else {
        printf("'%s' is not valid\n", test_input1);
    }

    if (validate_syntax(test_input2)) {
        printf("'%s' is valid\n", test_input2);
    } else {
        printf("'%s' is not valid\n", test_input2);
    }

    if (validate_syntax(test_input3)) {
        printf("'%s' is valid\n", test_input3);
    } else {
        printf("'%s' is not valid\n", test_input3);
    }

    return 0;
}*/