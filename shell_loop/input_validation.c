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
int invalid_input_checker(char *line)
{
    if (is_open_quotes(line) == 1 || bad_initial_char(line) == 1 
    || bad_final_char(line) == 1 || invalid_sequence(line) == 1
    || space_and_chars(line) == 1 || sized2_invalid(line) == 1)
        return 1;
    return 0;
}

/*
checks if command line is valid,
returns 0 if not
*/
int input_validation(char *line)
{
    if (*line == '\0' || is_space(line) == 1)
        return 0;
    else if (invalid_input_checker(line) == 1)
        return 0;
    else
        return 1;

}