/*#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct s_parsed_data
{
    char *path; //absolute path to executable
    char *cmd; //executable command, without args
    char **args; //command args
    char *simple_in_redir; //filename where stdin is redirected from
    char *simple_out_redir; //filename where stdout is redirected to
    char *here_doc; //delimiter to handle here_doc feature
    char *append; //filename to handle append redirection to stdout
    struct s_parsed_data *next;
} t_parsed_data;

void parse_add_node(t_parsed_data **head, t_parsed_data *new_node) 
{
    t_parsed_data *current;

    if (*head == NULL) 
        *head = new_node;
    else 
    {
        current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
    new_node->next = NULL; // Ensure the new node's next pointer is set to NULL
}*/

/*
**  returns new char ** where the modified
**  segment will be copied
**  auxiliary to parse_redir()
*/
/*char **alloc_cpy_segment(char **segment)
{
    int size;
    char **cpy_segment;

    size = 0;
    while(segment[size] != NULL)
        size++;
    cpy_segment = (char **)malloc((size + 1) * sizeof(char *));
    if (cpy_segment == NULL) 
        exit(1);
    return cpy_segment;
}*/

/*
**  fills the elements in cpy_segment with "0"s to signal further functions
**  that we're done with these elements.
**  @param: char ***cpy_segment is the address of the char ** created
**                   by alloc_cpy_segment()
** auxiliary to parse_redir()
*/
/*void mod_cpy_segment(char ***cpy_segment, int *i)
{
    (*cpy_segment)[*i] = strdup("0");
    (*cpy_segment)[*i + 1] = strdup("0");
    if ((*cpy_segment)[*i] == NULL || (*cpy_segment)[*i + 1] == NULL)
        exit(1);
    *i += 2;
}*/

/*
**  fills t_parsed_data struct with redirections data
** auxiliary to parse_redir()
*/
/*void handle_redir(char *redir, char *file, t_parsed_data *parsed_data) 
{
    if (strcmp(redir, "<") == 0)
        parsed_data->simple_in_redir = file;
    else if (strcmp(redir, ">") == 0)
        parsed_data->simple_out_redir = file;
    else if (strcmp(redir, ">>") == 0)
        parsed_data->append = file;
    else if (strcmp(redir, "<<") == 0)
        parsed_data->here_doc = file;
}*/

/*
**  Takes the original segment, fills the struct with redirection data
**  and fills a copy of char **segment with modified data to ignore
**  already parsed data
*/
/*char **parse_redir(t_parsed_data *parsed_data, char **segment)
 {
    int i;
    char **cpy_segment;

    i = 0;
    cpy_segment = alloc_cpy_segment(segment);
    while (segment[i] != NULL) 
    {
        if (strcmp(segment[i], "<") == 0 || strcmp(segment[i], ">") == 0
        || strcmp(segment[i], "<<") == 0 || strcmp(segment[i], ">>") == 0)
        {
            handle_redir(segment[i], segment[i+1], parsed_data);
            mod_cpy_segment(&cpy_segment, &i);
        }
        else 
        {
            cpy_segment[i] = strdup("1");
            i++;
        }
    }
    cpy_segment[i] = NULL; // Null-terminate the new array
    return cpy_segment;
}*/


/*handles
returns pointer to the head of the linked list
*/
/*t_parsed_data *parse_line(char **pipe_segment) 
{
    t_parsed_data *node;
    t_parsed_data *header; //pointer to the head of the linked list
	char **cpy_segment;

    node = (t_parsed_data *)malloc(sizeof(t_parsed_data));
    if (node == NULL)
        exit(1);
	node->path = NULL;
    node->cmd = NULL;
    node->args = NULL;
    node->simple_in_redir = NULL;
    node->simple_out_redir = NULL;
    node->here_doc = NULL;
    node->append = NULL;
    node->next = NULL;
    cpy_segment = parse_redir(node, pipe_segment); //fills node with redirection data
	int i = 0;
	while (cpy_segment[i] != NULL)
	{
		printf("cpy_segment %d is:%s\n", i, cpy_segment[i]);
		i++;
	}
    //parse_cmd(node, pipe_segment); //fills node with command data
    parse_add_node(&header, node); //add nodes to the bottom of the list

    return header;
}

int main(void)
{
	t_parsed_data *data;
	char *arr[] = {"<", "infile.txt", "\"cat\"", "file1", ">", "file2", "<<", "file3", NULL};
	int i = 0;
	while (arr[i] != NULL)
	{
		printf("arr %d is:%s\n", i, arr[i]);
		i++;
	}
	data = parse_line(arr);
	printf("data->path is:%s\n", data->path);
	printf("data->cmd is:%s\n", data->cmd);
	printf("data->simple_in_redir is:%s\n", data->simple_in_redir);
	printf("data->simple_out_redir is:%s\n", data->simple_out_redir);
	printf("data->here_doc is:%s\n", data->here_doc);
	printf("data->append is:%s\n", data->append);
	printf("data->next is: %p\n", (void *)data->next);

	return 0;
}*/