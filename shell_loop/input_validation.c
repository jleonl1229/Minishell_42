#include "../minishell.h"

/*
Approach with input validation: catch as many syntax errors as possible without going too crazy,
being aware that some will slip through, but expecting further parts of the code to flag them as
different types of errors.

Input can be invalid because quotes are not closed (ex. <" '>), 
certain chars are at the beginning ("|") or end of line(">"),
there is a non-valid sequence(||) or there are spaces between invalid sequence ("< <")

Returns 0 if not valid
*/
/*int is_valid_cl(char *line)
{
    //if is_open_quotes(line) == 1 || char_beginning(line) ==1 || char_end(line) == 1
    //|| spaces_between_chars(line) == 1 || forbidden_sequence(line) == 1
        //return 0
    

}*/

/*
checks if command line is valid,
returns 0 if not
*/
/*int input_validation (char *line)
{
    if (*line = '\0' || is_space(line) == 1)
        return 0;
    else if (is_valid_cl(line) == 0)
    {
        return 0;
    }
    else
        //correct input

}*/