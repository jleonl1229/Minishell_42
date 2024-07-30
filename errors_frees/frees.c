#include "../minishell.h"

char	**free_matrix(char **pointer)
{
	int	i;

	i = 0;
    if (pointer == NULL)
        return NULL;
    while (pointer[i] != NULL)
	{
		free(pointer[i]);
        pointer[i] = NULL;
		++i;
	}
	free(pointer);
    pointer = NULL;
	return (NULL);
}

void free_env_list(t_env *head) 
{
    t_env *current;
    t_env *next_node;

    current = head;
    while (current != NULL) 
    {
        next_node = current->next;
        free(current->env_name); // Free the duplicated env_name
        free(current->env_value); // Free the duplicated env_value
        free(current); // Free the node itself
        current = next_node;
    }
}

/*
**  frees every element in t_parsed_struct
**  to be called at the end of the loop iteration,
**  before parsing the next user prompt
*/
void    free_parsing_list(t_sh_data **sh)
{
    t_parsed_data *current;
    t_parsed_data *next_node;

    current = (*sh)->parsed_header;
    while(current != NULL)
    {
        next_node = current->next;
        //if (current->cmd != NULL)
        free(current->cmd);
        //if (current->args != NULL) //modified free_matrix by adding pointer == null condition checker
        free_matrix(current->args);
        free(current->simple_in_redir);
        free(current->simple_out_redir);
        free(current->append);
        free(current->here_doc);
        free(current);
        current = next_node;
    }
}

/*
**  function called when dup_env(), bad_initial_char() or bad_final_char() error
**
*/
void pre_parse_cleanup(t_sh_data **sh, t_env **header, char ***org)
{
    if (org != NULL)
        free_matrix(*org);
    if ((*sh)->env_header != NULL)
        free_env_list((*sh)->env_header);
    else
        free_env_list(*header);
    if((*sh)->prev_line != NULL)
        free((*sh)->prev_line);
    free(*sh);
    printf("malloc error\n");
    exit(1);
}

void parsing_cleanup(t_sh_data **sh, char **pipe_segments, char **split_space)
{
    free((*sh)->new_line);
    if (pipe_segments != NULL)
        free_matrix(pipe_segments);
    if (split_space != NULL)
        free_matrix(split_space);
    pre_parse_cleanup(sh, 0, 0);


}

/*TO BE ADDED HERE: Think which functions are in need
 of which type of free function. For example: split_by_pipe()
 needs to call free_split()

*/


/* TO BE ADDED HERE (maybe it should go on utils folder?): 
 * when exiting (due to error, etc.) these functions
   will clean malloc-ed memory to prevent leaks
 */


/*used to free an array of strings*/
/*void free_split(char **segments) 
{
    int i;
	
	i = 0;
    while (segments[i] != NULL) 
	{
        free(segments[i]);
        i++;
    }
    free(segments);
}*/