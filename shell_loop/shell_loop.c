#include "../minishell.h"


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
            append_line(sh, line);
        else
        {
            if (sh->prev_line == NULL || (ft_strncmp(line, sh->prev_line, ft_strlen(sh->prev_line)) != 0
            || ft_strncmp(line, sh->prev_line, ft_strlen(line)) != 0))
            {
                add_history(line);
                free(sh->prev_line);
                sh->prev_line = ft_strdup(line);
            }
        }
    }
    return 0;
}

int get_input(t_sh_data *sh, char *line, int e_pipe)
{
    char *str;

    printf("epipe is: %d\n", e_pipe);
    if(e_pipe == 0)
        str = "$ "; 
    else
        str = "> ";
    line = readline(str);
    return (save_to_history(sh, line, e_pipe));

}

void shell_loop(t_sh_data **sh)
{
    char *line;
    int e_pipe;
    int checker;

    line = NULL;
    e_pipe = 0;
    while (1)
    {
        //signals (need to be reset every time? could it go before while loop?)
        e_pipe = get_input(*sh, line, e_pipe);
        checker = input_validation((*sh)->prev_line, sh);
        if (checker == 0)
            continue;
        else if (checker == 7)
        {
            e_pipe = 1;
            continue;
        }
        (*sh)->parsed_header = parsing(*sh); //(*sh)->prev_line as parameter can be ommited
        /*int i;
        while((*sh)->parsed_header != NULL)
        {
            printf("sh->parsed_header->cmd is: %s\n", (*sh)->parsed_header->cmd);
            i = 0;
            while((*sh)->parsed_header->args[i] != NULL)
            {
                printf("sh->parsed_header->args %d is: %s\n", i, (*sh)->parsed_header->args[i]);
                i++;
            }
            printf("sh->parsed_header->simple_in_redir is: %s\n", (*sh)->parsed_header->simple_in_redir);
            printf("sh->parsed_header->simple_out_redir is: %s\n", (*sh)->parsed_header->simple_out_redir);
            printf("sh->parsed_header->here_doc is: %s\n", (*sh)->parsed_header->here_doc);
            printf("sh->parsed_header->append is: %s\n", (*sh)->parsed_header->append);
            printf("sh->parsed_header->next is: %p\n", (void *)(*sh)->parsed_header->next);           
            (*sh)->parsed_header = (*sh)->parsed_header->next;
             printf("sh->parsed_header is %p\n", (*sh)->parsed_header);
        }*/
        free(line);
        free((*sh)->new_line);
        (*sh)->new_line = NULL;
        free_parsing_list(sh);
        if (ft_strncmp((*sh)->prev_line, "exit", ft_strlen("exit")) == 0)
        {
            write(1, "exit\n", ft_strlen("exit\n"));
            break;
        }
        write(1, (*sh)->prev_line, ft_strlen((*sh)->prev_line));
        write(1, "\n",1);
    }
    //frees when exiting program successfully
    free_env_list((*sh)->env_header);
    free((*sh)->prev_line);
    free(*sh);

    
    
}
