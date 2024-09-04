#include "../minishell.h"

int signal_received = 0; //global var definition

int ignore_history(char *line)
{
    char *no_history;
    int i;

    no_history = " \t\n\v\f\r";
    i = 0;
    if (line[0] == '\0')
        return 1;
    while (no_history[i] != '\0')
    {
        if (no_history[i] == line[0])
            return 1;
        i++;
    }
    return 0;
}


int append_line(t_sh_data *sh, char *line)
{
    char *new_line;
    int len;

    len = ft_strlen(sh->prev_line) + ft_strlen(line) + 1;
    new_line = malloc(len);
    if (new_line == NULL)
        pre_parse_cleanup(&sh, NULL, NULL);
    ft_strlcpy(new_line, sh->prev_line, len);
    ft_strlcat(new_line, line, len);
    if (ignore_history(line) == 0)
        add_history(new_line);
    free(sh->prev_line);
    sh->prev_line = new_line;

    return 0;
}

int save_to_history(t_sh_data *sh, char *line, int e_pipe) 
{
    if (line != NULL)
    {
        if (e_pipe == 1)
        {
            append_line(sh, line);
        }
        else
        {
            if (sh->prev_line == NULL || (ft_strncmp(line, sh->prev_line, ft_strlen(sh->prev_line)) != 0
            || ft_strncmp(line, sh->prev_line, ft_strlen(line)) != 0))
            {
               if (bad_final_char(line, &sh, 0) != 7 && ignore_history(line) == 0)
                    add_history(line);
                free(sh->prev_line);
                sh->prev_line = ft_strdup(line);
                if (sh->prev_line == NULL)
                    pre_parse_cleanup(&sh, NULL, NULL);
            }
        }
    }
    return 0;
}

/*
**  e_pipe = 1 means that an ending pipe prompt has been introduced
**  signal_received = 3 means that the SIGINT handler has been triggered for an ending pipe prompt
** readline sends an EOF signal and returns NULL if CTRL +D is pressed.
*/
int get_input(t_sh_data *sh, char *line, int e_pipe)
{
    char *str;

    if(e_pipe == 0)
        str = "$ "; 
    else
        str = "> ";
    line = readline(str);
    if (line == NULL)
    {
        printf("exit\n");
        pre_parse_cleanup(&sh, NULL, NULL);
    }
    if (e_pipe == 1 && signal_received == 3)
    {
        e_pipe = 0;
        signal_received = 0;
    }
    return (save_to_history(sh, line, e_pipe));
}

/*
**  blocking_cmd_sig() registers specific signal handling for blocking commands (example:
**  cat without arguments, which waits for user input).
**  checker = 0 means: user entered invalid input, an empty string or only space
**  checker = 7 means: user entered a command with an ending pipe
**  ""(*sh)->parsed_header == NULL"" will be true if SIGINT caught in heredoc
*/
void shell_loop(t_sh_data **sh, int checker, int e_pipe)
{
    char *line;

    line = NULL;
    while (1)
    {
        //TO BE TESTED:
        /*if (signal_received == 1 || signal_received == 6 || signal_received == 3)
        {
            printf("here\n");
            free((*sh)->last_exit_status);
            (*sh)->last_exit_status = ft_strdup("130");
        }
        else if (signal_received == 7)
        {
            free((*sh)->last_exit_status);
            (*sh)->last_exit_status = ft_strdup("131");
        }*/
        default_signals();
        e_pipe = get_input(*sh, line, e_pipe);
        blocking_cmd_sig();
        checker = input_validation((*sh)->prev_line, sh);
        if (checker == 0)
            continue;
        else if (checker == 7)
        {
            signal_received = 2;      
            e_pipe = 1;
            continue;
        }
        (*sh)->parsed_header = parsing(*sh, NULL, 0);
        if ((*sh)->parsed_header == NULL)
            continue;
        piping(*sh);
        frees_before_next_ite(line, sh);
        if (ft_strncmp((*sh)->prev_line, "exit", ft_strlen("exit")) == 0)
        {
            write(1, "exit\n", ft_strlen("exit\n"));
            break;
        }
    }
}
