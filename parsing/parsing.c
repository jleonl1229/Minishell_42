#include "../minishell.h"

/*
split command line into pipe segments
*/
char **split_by_pipe(char *line, int start, int segment_index, int i) 
{
    int segments;
    char **result;

	segments = count_segments(line);
	result = malloc((segments + 1) * sizeof(char *));
	if (result == NULL)
		return NULL;
    while(segment_index < segments) 
	{
        if (line[i] == '\'' || line[i] == '"')
            skip_quotes(line, &i);
        if (line[i] == '|' || line[i] == '\0')
		{
            result[segment_index] = malloc((i - start + 1) * sizeof(char));
			if(result[segment_index] == NULL)
				return free_matrix(result);
            ft_strlcpy(result[segment_index], line + start, i - start + 1);
            segment_index++;
            start = i + 1;
        }
		i++;
    }
    result[segments] = NULL;
    return result;
}

/*
**  auxiliary to parse_line()
*/
void parsed_node_init(t_parsed_data *node)
{
    node->path = NULL; //could use an initi funct for these
    node->cmd = NULL;
    node->simple_in_redir = -2; //useful value to check at execution
    node ->last_fd = -2;
    node->here_doc = NULL;
    node->next = NULL;

}

/* 
    *initializes a new t_parsed_data node and handles functions to fill the node with data
    *   @param: an array of strings, representing a pipe segment
    *    splitted by spaces.
    *   returns pointer to the head of the linked list
*/
void parse_line(t_sh_data **sh, t_parsed_data **header, char **split_space, char **pipe_segments) 
{
    t_parsed_data *node;
	result res;

    node = (t_parsed_data *)malloc(sizeof(t_parsed_data)); // to be freed with list
	if (node == NULL)
		parsing_cleanup(sh, pipe_segments, split_space);
    parsed_node_init(node);
    res = parse_redir(node, split_space);
    if (res.error_code == 2)
    {
        free(node);
        printf("parse_redir\n");
        parsing_cleanup(sh, pipe_segments, split_space);
    }
    else if (res.error_code == 1) //SIGINT caught
    {
        //printf("parse_line(): sigint caught\n");
        free(node);
        free((*sh)->new_line);
        free_matrix(pipe_segments);
        free_matrix(split_space);
        // free((*sh)->prev_line);?
        return;
    }
    if (parse_cmd_and_path(*sh, node, split_space, res.str_arr) == -1)
    {
        free(node);
        printf("parse_cmd_and_path\n");
        parsing_cleanup(sh, pipe_segments, split_space);
    }
    parse_add_node(header, node); //add nodes to the bottom of the list*/
}

t_parsed_data *parsing(t_sh_data *sh)
{
	char **pipe_segments;
	int i;
	char **split_space;
	t_parsed_data *head;

	i = 0;
	add_space(sh);
	pipe_segments = split_by_pipe(sh->new_line, 0, 0, 0);
	if(pipe_segments == NULL)
        parsing_cleanup(&sh, 0, 0);
    head = NULL;
	while(pipe_segments[i] != NULL)
	{
		split_space = ft_split_quotes(pipe_segments[i++], ' ');
        if (split_space == NULL)
            parsing_cleanup(&sh, pipe_segments, 0);
        split_space = env_parse (0, 0, split_space, sh->env_header);
        if (split_space == NULL)
            parsing_cleanup(&sh, pipe_segments, split_space);
		parse_line(&sh, &head, split_space, pipe_segments);
        //printf("signal_received is: %d\n", signal_received);
        if (signal_received == 1)
        {
            //printf("parsing(): sigint caught\n");
            signal_received = 0;
            return NULL;
        }
        free_matrix(split_space); 
	}
    free_matrix(pipe_segments);
    return head;
}
