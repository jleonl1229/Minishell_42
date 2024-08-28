/*#include "../minishell.h"

OVER COMPLICATED MYSELF, KEEPING THESE JUST IN CASE

char *env_concat(t_env *env, char **envp) 
{
    int size;
    char *env_var;
    int s_value;
    
    if (env->env_value == NULL)
        s_value = 0;
    else
        s_value = ft_strlen(env->env_value);
    size = ft_strlen(env->env_name) + 1 + s_value + 1; // +1 for '=' and +1 for '\0'
    env_var = malloc(size);
    if (env_var == NULL)
    {
        free_matrix(envp);
        return NULL;
    }
    env_var[0] = '\0';
    ft_strlcat(env_var, env->env_name, size);
    ft_strlcat(env_var, "=", size);
    ft_strlcpy(env_var + ft_strlen(env_var), env->env_value, s_value +1);

    return env_var;
}


char **alloc_char_env(t_env *header)
{
    int i;
    char **env;

    i = 0;
    while (header != NULL) 
    {
        header = header->next;
        i++;
    }
    env = malloc(sizeof(char *) * (i + 1));
    if (env == NULL)
        return NULL;
    return env;

}

char **tenv_to_char(t_env *header) 
{
    t_env *temp;
    int i;
    char **env_arr; // Pointer to the head of char * array

    temp = header;
    i = 0;
    env_arr = alloc_char_env(temp);
    if (env_arr == NULL)
        return NULL;
    while (temp != NULL) 
    {
        env_arr[i] = env_concat(temp, env_arr);
        if (env_arr[i] == NULL) 
        {
            printf("alloc_for_env(): env_concat failure\n");
            return NULL;
        }
        i++;
        temp = temp->next;
    }
    env_arr[i] = NULL;
    return env_arr;
}
*/