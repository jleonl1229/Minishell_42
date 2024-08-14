#include "../minishell.h"

/*
1- Count the number of environment variables in the linked list.
2- Allocate memory for the char ** array.
3- Iterate through the linked list and format each env_name and env_value into a single string.
4- Store each formatted string in the char ** array.
5- Set the last element of the array to NULL.

*/

int alloc_env_var(t_env *header)
{
    return ft_strlen(header->env_name) + ft_strlen(env_value) + 1 //+1 for "=" 
}

char **alloc_for_env(t_env *header)
{
    t_env *temp;
    int i;
    char **env_arr;

    temp = header;
    i = 0;
    while(temp != NULL)
    {
        temp = temp->next;
        i++;
    }
    env_arr = malloc(sizeof(char *) * (i + 1));
    if (env_arr == NULL)
        printf("alloc_for_env(): malloc failure");
    temp = header;
    i = 0;
    while (temp !=  NULL)
    {
        env_arr[i] = malloc(sizeof(char *) * (alloc_env_var(header) + 1));
    }

}
