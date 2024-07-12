#include "../minishell.h"


/*
saves input to history if line is not null and line is not equal to previous line
*/
void save_to_history(t_sh_data *sh, char *line) 
{
    if (line != NULL && (sh->prev_line == NULL || ft_strncmp(line, sh->prev_line, ft_strlen(line)) != 0))
    {
        add_history(line);
        sh->prev_line = line;
    }
}

/*
uses readline to show prompt and retrieve inputed line
 */
char    *get_input(char *line)
{
    char *str;

    str = "$ "; //prompt
    line = readline(str); //the line returned by readline uses  malloc
    printf("line is: %s\n", line);
    return line;
}

void shell_loop(t_sh_data *sh)
{
    char *line;
    printf("first env is: %s\n", sh->env_header->env_name);

    while (1)
    {
        //signals (need to be reset every time? could it go before while loop?)
        line = get_input(line);
        save_to_history(sh, line);
        //if (input_valid(line) == 0)
            //continue (skip everything else and start the loop again)
        //parsing
        if (ft_strncmp(line, "exit", ft_strlen("exit")) == 0)
        {
            write(1, "exit\n", ft_strlen("exit\n"));
            break;
        }
        write(1, line, ft_strlen(line));
        write(1, "\n",1);

    }
}