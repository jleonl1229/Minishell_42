#include "../minishell.h"


int is_simple_cmd(t_sh_data *sh)
{
    if (sh->parsed_header->next == NULL)
        return 1;
    return 0;

}


void add_shenv_var(t_sh_data *sh, char **new_env, char *cmd)
{
    int i;

    i = 0;
    while (new_env[i] != NULL)
        i++;
    new_env[i] = ft_strdup(cmd);
    if (new_env[i] == NULL)
        sh->env = NULL;
}

/*
** duplicates sh->env
*/
char **dup_sh_env(char **env, int set)
{
    char **new_env;
    int i;

    i = 0;
    while(env[i] != NULL)
        i++;
    if (set == -1)
        new_env = malloc(sizeof(char *)* (i + 2)); //+ 1 for new env_var + 1 for NULL
    else
        new_env = malloc(sizeof(char *)* (i + 1)); // + 1 for NULL 
    if (new_env == NULL)
        return NULL;
    new_env[i] = NULL;
    if (set == -1)
        new_env[i+1] = NULL;
    i= 0;
    while(env[i] != NULL)
    {
        new_env[i] = ft_strdup(env[i]);
        i++;
    }
    free_matrix(env);
    return new_env;
}

/*
**  need to check if is_var_set:
**      if it is:
**          if var_value ->replace str
**      if it is not ->add str
**  int set: the position in the char ** where the existing env var is placed  
**  char *cmd: the env var. examples: "MY_VAR"(unassigned) or "MY_VAR=hey"
*/
void mini_export_execve_edition(t_sh_data *sh, int set, char *cmd)
{
    char **new_env;
    char *var_value;

    new_env = dup_sh_env(sh->env, set); //need to free new_env
    if (new_env == NULL)
        printf("mini_export_execve_edition(): malloc failure\n"); //needs to exit
    if (set != -1) //existing env_var
    {
        var_value = ft_strchr(cmd, '=');
        if (var_value != NULL) //assigned
        {
            free(new_env[set]);
            new_env[set] = ft_strdup(cmd);
            if (new_env[set] == NULL)
                printf("mini_export_execve_edition(): malloc failure2\n"); //needs to exit
        }
    }
    else
        add_shenv_var(sh, new_env, cmd);
    sh->env = new_env;
    if (sh->env == NULL)
        printf("mini_export_execve_edition(): something went wrong\n"); //needs to exit  
}
