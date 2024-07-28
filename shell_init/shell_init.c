#include "../minishell.h"


/*makes a copy of env and stores it in a linked list data structure.
t_sh_data gets a pointer to the head
*/
t_env *dup_env(char **envp, t_env *header, t_sh_data **sh)
{
    char *var_name;
    char *var_content;
    char **a_env;
    char **org;
    t_env *new_node;

    while (*envp != NULL)
    {
        a_env = ft_split(*envp, '=');
        org = a_env;
        if (a_env == NULL || *a_env == NULL)
            pre_parse_cleanup(sh, &header, &org);
        var_name = *a_env;
        var_content = *(++a_env);
        new_node = env_create_node(var_name, var_content);
        if (new_node == NULL)
            pre_parse_cleanup(sh, &header, &org);
        env_add_node(&header, new_node);
        free_matrix(org);
        envp++;
    }
    return header;
}

/* ** (MORE CODE WILL BE ADDED HERE AS WE ADVANCE ON THE PROJECT)
    **  to be done before infinite loop, when program is launched
    **  @param1:    
*/
void shell_init(t_sh_data **sh, char **envp)
{
    t_env *header;

    header = NULL;
    if (!isatty(STDIN_FILENO)) //safeguard that checks if minishell input coming from terminal
    {
        free(*sh);
        perror("terminal is not STDIN");
		exit(EXIT_SUCCESS);
    }
    (*sh)->env_header = NULL;
    (*sh)->prev_line = NULL; //only null whe initialized
    (*sh)->parsed_header = NULL;
    (*sh)->env_header = dup_env(envp, header, sh); //copies envp in sh->env_header
}
