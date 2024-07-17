#include "../minishell.h"


/*Counts number of pipe segments in a 
command line instruction.
Example:"echo hello > out | cat out | wc -l" returns 3
auxiliary to split_by_pipe() function
*/
/*int count_segments(char *str) 
{
    int count;
	int i;
	
	count = 1;
	i = 0;
    while (str[i] != '\0')
	{
        if (str[i] == '\'' || str[i] == '"')
            skip_quotes(str, &i);
        if (str[i] == '|')
            count++;
		i++;
    }
    return count;
}*/
