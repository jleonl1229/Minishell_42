
#include "minishell.h"


/*makes a copy of env and stores it in a linked list data structure.
t_sh_data gets a pointer to the head
*/
t_env *dup_env(char **envp)
{
    char *var_name;
    char *var_content;
    char **a_env;
    t_env *new_node;
    t_env *header;
    /*not checking if envp or *envp are null because checked in env_checker, 
    but might be good practice to do so*/
    header = NULL;
    while (*envp != NULL)
    {
        a_env = ft_split(*envp, '=');
        if (a_env == NULL || *a_env == NULL)
        {
            //exit with error
        }
        var_name = *a_env;
        var_content = *(++a_env);
        new_node = env_create_node(var_name, var_content);
        printf("env_name is: %s and env_value is: %s\n", new_node->env_name, new_node->env_value);
        if (new_node == NULL)
        {
            //exit with error
        }
        env_add_node(&header, new_node);
        envp++;
    }
    return header;
}


/* ** (MORE CODE WILL BE ADDED HERE AS WE ADVANCE ON THE PROJECT)
    **  to be done before infinite loop, when program is launched
    **  @param1:    
*/
void shell_init(t_sh_data *sh, char **envp)
{
    if (!isatty(STDIN_FILENO)) //checks if minishell input coming from terminal
    {
		//exit with error
    }
    sh->env_header = dup_env(envp); //copies envp in sh->env_header

}

/*
 */
char    *get_input(char *line)
{
    char *str;

    str = "$ ";
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
        //signals
        //terminal_prompt
        line = get_input(line);
        add_history(line);
        //is_input_valid(line)
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



/*if PATH is null the shell can't execute non-built-in programs, 
    but should this check be made in a future step and here just check if env is null? Probably yes
    PATH can be deleted with this command: "unset PATH"
    envp can be null, and so no PATH be found
    env can be non null, but no PATH be found

*/
void env_checker(char **envp)
{
    int path_found;

    path_found = 0;
    if ( envp == NULL || *envp == NULL)
    {
        perror("No ENV found, don't delete ENVs!");
        exit(EXIT_SUCCESS);
    }
    while (*envp != NULL)
    {
        if (ft_strncmp(*envp, "PATH=", ft_strlen("PATH=")) == 0)
        {
            path_found = 1;
            break;
        }
        envp++;
    }
    if (path_found == 0)
    {
        perror("No PATH found, don't delete the PATH env!");
        exit(EXIT_SUCCESS);
    }
}

// exits program if argc is not 1
void	argc_checker(int argc)
{
    if (argc != 1)
    {
        perror("Invalid argument count. Usage: ./minishell");
        exit(EXIT_SUCCESS);
    }

}


int main(int argc, char **argv, char **envp)
{
    t_sh_data sh;

    printf("argv[0] is: %s\n", argv[0]);
    argc_checker(argc);
        //exit error if argc > 1
    env_checker(envp);
        //exit error if envp or *envp NULL
    printf("entering shell init...\n");
    shell_init(&sh, envp);
    shell_loop(&sh);
    return 0;
}