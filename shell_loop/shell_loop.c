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
               if (bad_final_char(line, &sh) != 7 && ignore_history(line) == 0)
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
    printf("line is: %s\n", line);
    return (save_to_history(sh, line, e_pipe));
}

/*
**  def_signals() inside loop to restart to the signal handler defined in def_signals.
**  otherwise had problems with sig_blocking_cmd()
** ""(*sh)->parsed_header == NULL"" will be true if SIGINT caught in heredoc
*/
void shell_loop(t_sh_data **sh)
{
    char *line;
    int e_pipe;
    int checker;

    line = NULL;
    e_pipe = 0;
    while (1)
    {
       /* if (isatty(0)) {
        printf("STDIN is a terminal\n");
        } else {
        printf("STDIN is not a terminal\n");
        }*/
        //printf("signal received is: %d\n", signal_received);
        if (signal_received == 0) //default value, no signal triggered
            def_signals();
        else if (signal_received == 2) //ending pipe registered
        {
            signal_received = 0;
            ending_pipe_sig();
        }
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
        (*sh)->parsed_header = parsing(*sh);
        //printf("sh->parsed_header = %s\n", (char *)(*sh)->parsed_header);
        if ((*sh)->parsed_header == NULL) //SIGINT caught at the heredoc level
            continue;
        piping(*sh);
        //frees before starting loop again
        free(line);
        free((*sh)->new_line);
        (*sh)->new_line = NULL;
        free_parsing_list(sh);
        if (ft_strncmp((*sh)->prev_line, "exit", ft_strlen("exit")) == 0)
        {
            write(1, "exit\n", ft_strlen("exit\n"));
            break;
        }
        //write(1, (*sh)->prev_line, ft_strlen((*sh)->prev_line));
        //write(1, "\n",1);
    }
    //frees when exiting program successfully
    free_env_list((*sh)->env_header);
    free((*sh)->prev_line);
    free(*sh); //malloced in main

    
    
}

//THIS CODE GOES BETWEEN piping() and "frees before starting loop again"
/*int i;
        while((*sh)->parsed_header != NULL)
        {
            printf("sh->parsed_header->path is: %s\n", (*sh)->parsed_header->path);
            i = 0;
            if ((*sh)->parsed_header->cmd != NULL)
            {
                while((*sh)->parsed_header->cmd[i] != NULL)
                {
                    printf("sh->parsed_header->cmd %d is: %s\n", i, (*sh)->parsed_header->cmd[i]);
                    i++;
                }
            }
            printf("sh->parsed_header->simple_in_redir is: %d\n", (*sh)->parsed_header->simple_in_redir);
            printf("sh->parsed_header->simple_out_redir is: %d\n", (*sh)->parsed_header->simple_out_redir);
            t_list *temp;
            temp = (*sh)->parsed_header->here_doc;
            while (temp != NULL)
            {
                printf("sh->parsed_header->here_doc is: %s\n", (char *)temp->content);
                temp = temp->next;
            }
            printf("sh->parsed_header->here_doc is: %p\n", temp);
            printf("sh->parsed_header->append is: %d\n", (*sh)->parsed_header->append);
            printf("sh->parsed_header->next is: %p\n", (void *)(*sh)->parsed_header->next);           
            (*sh)->parsed_header = (*sh)->parsed_header->next;
             printf("sh->parsed_header is %p\n", (*sh)->parsed_header);
        }*/