

/*
**  saves input to history if line is not null and line is not equal to previous line
*/
/*void save_to_history(t_sh_data *sh, char *line) 
{
    if (line != NULL && (sh->prev_line == NULL || ft_strncmp(line, sh->prev_line, ft_strlen(line)) != 0))
    {
        add_history(line);
        free(sh->prev_line);
        sh->prev_line = ft_strdup(line);

    }
}*/

/*
**  uses readline to show prompt and retrieve inputed line
 */
/*char    *get_input(char *line)
{
    char *str;

    str = "$ "; //prompt
    line = readline(str); //the line returned by readline uses  malloc
    return line;
}*/


/*void shell_loop(t_sh_data **sh)
{
    char *line;

    while (1)
    {
        //signals (need to be reset every time? could it go before while loop?)
        line = get_input(line);
        save_to_history(*sh, line);
        if (input_validation(line, sh) == 0)
            continue; //(skip everything else and start the loop again)
        //sh->parsed_header = parsing(sh, line);
        if (ft_strncmp(line, "exit", ft_strlen("exit")) == 0)
        {
            write(1, "exit\n", ft_strlen("exit\n"));
            break;
        }
        write(1, line, ft_strlen(line));
        write(1, "\n",1);*/

        /*int i;
        while(sh->parsed_header != NULL)
        {
            printf("sh->parsed_header->cmd is: %s\n", sh->parsed_header->cmd);
            i = 0;
            while(sh->parsed_header->args[i] != NULL)
            {
                printf("sh->parsed_header->args %d is: %s\n", i, sh->parsed_header->args[i]);
                i++;
            }
            printf("sh->parsed_header->simple_in_redir is: %s\n", sh->parsed_header->simple_in_redir);
            printf("sh->parsed_header->simple_out_redir is: %s\n", sh->parsed_header->simple_out_redir);
            printf("sh->parsed_header->here_doc is: %s\n", sh->parsed_header->here_doc);
            printf("sh->parsed_header->append is: %s\n", sh->parsed_header->append);
            printf("sh->parsed_header->next is: %p\n", (void *)sh->parsed_header->next);           
            sh->parsed_header = sh->parsed_header->next;
        }*/
        /*free(line);
    }
    //frees when exiting program successfully
    free_env_list((*sh)->env_header);
    free((*sh)->prev_line);
    free(*sh);
    
}*/