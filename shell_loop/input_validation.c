#include "../minishell.h"



/*
input can be invalid because quotes are not closed (ex. <" '>), 
certain chars are at the beginning ("|") or end of line(">"),
there is a non-valid sequence(||) 
or are spaces between invalid sequence ("< <")
*/
/*int invalid_cl(char *line)
{

}*/

/*
checks if command line is valid,
returns 0 if not
*/
/*int input_validation (char *line)
{
    if (*line = '\0' || is_space(line) == 1)
        return 0;
    else if (invalid_cl(line) == 1)
    {
        return 0;
    }



}*/