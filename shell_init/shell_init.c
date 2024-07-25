#include "../minishell.h"


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
    sh->prev_line = NULL; //only null whe initialized
    sh->parsed_header = NULL;
}