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

void free_tlist(t_list *header)
{
    t_list *temp;

    if (header == NULL)
        return;
    while (header != NULL)
    {
        temp = header->next;
        free(header->content);
        free(header);
        header = temp;
    }
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
        free_matrix(current->cmd);
        free(current->path);
        free(current);
        current = next_node;
    }
}

/*
**  function called when dup_env(), bad_initial_char() or bad_final_char() error
**
*/
void pre_parse_cleanup(t_sh_data **sh, t_env *header, char **org)
{
    if (org != NULL)
        free_matrix(org);
    if ((*sh)->env_header != NULL)
        free_env_list((*sh)->env_header);
    else
        free_env_list(header);
    if((*sh)->prev_line != NULL)
        free((*sh)->prev_line);
    free(*sh);
    //printf("malloc error\n");
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

void frees_before_next_ite(char *line, t_sh_data **sh)
{
    free(line);
    free((*sh)->new_line);
    (*sh)->new_line = NULL;
    free_parsing_list(sh);
}

void free_hdoc_sigint(t_parsed_data *node, t_sh_data *sh, char **p_seg, char **splt_sp)
{
    free(node);
    free(sh->new_line);
    free_matrix(p_seg);
    free_matrix(splt_sp);
}
result free_parse_redir(result res, int flag, t_parsed_data *parsed_data)
{
    free_tlist(parsed_data->here_doc);
    free_matrix(res.str_arr);
    res.str_arr = NULL;
    if (flag == -1)
        res.error_code = 2;
    else
        res.error_code = 1;
    return res;
}