#include "../minishell.h"

char *rs_alloc_new_str(char *input, int lex_len)
{
    int new_str_len;
    char *found;
    char *new_str;

    new_str_len = 0;
    // Calculate the length of the new string
    while ((found = ft_strnstr(input, "_LAST_EXIT_STATUS_", ft_strlen(input))) != NULL) 
    {
        new_str_len += (found - input) + lex_len;
        input = found + ft_strlen("_LAST_EXIT_STATUS_");
    }
    if (new_str_len == 0)
        return NULL;
    new_str_len += strlen(input); // Add the length of the remaining part
    // Allocate memory for the new string
    new_str = (char *)malloc(new_str_len + 1); 
    //printf("new_str_len is: %d\n", new_str_len +1);
    if (new_str == NULL) 
    {
        printf("rs_new_str(): malloc error\n"); 
        //need to cleanup
    }
    return new_str;
}

char *rs_build_new_str(char *input, t_sh_data *sh, char *new_str, int lex_len)
{
    char *found;
    int prefix;
    char *str_iter;

    str_iter = new_str;
    while ((found = ft_strnstr(input, "_LAST_EXIT_STATUS_", ft_strlen(input))) != NULL) 
    {
        prefix = found - input;
        // Copy the prefix
        //strncpy(new_str_ptr, current_pos, prefix_len);
        ft_strlcpy(str_iter, input, prefix +1);
        //printf("str_iter is: %s\n", str_iter);
        str_iter += prefix;
        // Copy the last exit status
        //strcpy(new_str_ptr, sh->last_exit_status);
        ft_strlcpy(str_iter, sh->last_exit_status, ft_strlen(sh->last_exit_status) +1);
        //printf("str_iter is: %s\n", str_iter);
        str_iter += lex_len;
        // Move the current position pointer
        input = found + strlen("_LAST_EXIT_STATUS_");
    }
    // Copy the remaining part of the original string
    ft_strlcpy(str_iter, input, (input - str_iter) + 1);
    //printf("str_iter is: %s\n", str_iter);
    //printf("new_str is: ")
    return new_str;
}

void cmd_return_status(t_sh_data *sh, char **input) 
{
    int i;
    char *exp_str;
    int lex_len;
    
    i = 0;
    if (sh->last_exit_status == NULL)
        lex_len = 0;
    else
        lex_len = ft_strlen(sh->last_exit_status);
    while (input[i] != NULL) 
    {
        exp_str = rs_alloc_new_str(input[i], lex_len);
        //printf("ft_strlen(exp_str) is: %ld\n", ft_strlen(exp_str))
        if (exp_str == NULL) //no need to built the new str
        {
            i++;
            continue;
        }
        exp_str = rs_build_new_str(input[i], sh, exp_str, lex_len);
        // Free the old string and update the pointer
        free(input[i]);
        input[i] = strdup(exp_str);
        i++;
    }
}