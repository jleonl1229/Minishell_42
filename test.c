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