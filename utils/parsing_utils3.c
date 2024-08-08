/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:44:20 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/07/29 12:42:19 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../minishell.h"


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
     new_node->next = NULL;
 }

 /*
 **  returns new char ** where the modified
 **  segment will be copied
 **  auxiliary to parse_redir()
 */
 char **alloc_cpy_segment(char **segment)
 {
     int size;
     char **cpy_segment;

     size = 0;
     while(segment[size] != NULL)
         size++;
     cpy_segment = (char **)malloc((size + 1) * sizeof(char *));
     if (cpy_segment == NULL) 
         return NULL;
     return cpy_segment;
 }

 /*
 **  fills the elements in cpy_segment with "0"s to signal further functions
 **  that we're done with these elements.
 **  @param: char ***cpy_segment is the address of the char ** created
 **                   by alloc_cpy_segment()
 ** auxiliary to parse_redir()
 */
 int mod_cpy_segment(char **cpy_segment, int i, t_parsed_data *parsed_data, char **segment)
 {
    while (segment[i] != NULL) 
    {
        if (ft_strncmp(segment[i], "<", ft_strlen(segment[i])) == 0
        || ft_strncmp(segment[i], ">", ft_strlen(segment[i])) == 0
        || ft_strncmp(segment[i], "<<", ft_strlen(segment[i])) == 0
        || ft_strncmp(segment[i], ">>", ft_strlen(segment[i])) == 0)
        {
            if (handle_redir(segment[i], segment[i+1], parsed_data) == 0 )
            {
                cpy_segment[i] = NULL;
                return -1;
            }
            cpy_segment[i] = ft_strdup("0");
            cpy_segment[i + 1] = ft_strdup("0");
            if (cpy_segment[i] == NULL || cpy_segment[i + 1] == NULL)
                return -1;
            i += 2;
        }
        else
            if ((cpy_segment[i++] = ft_strdup("1")) == NULL)
                return -1;
    }
    cpy_segment[i] = NULL;
    return 0;
 }

/*
**  simple_in_redir initialized to -2.
**  if return 0, terminate current command but don't exit program, 
**  keep listening for new commands
** auxiliary to handle_redir()
*/
int redir_fd(int *redir, char *file, char *redir_type)
{
    int fd;

    fd = 0;
    if (*redir == -1)
        return 1;
    if (*redir != -2)
    {
        fd = close(*redir);
        if (fd == -1)
        {
            printf("redir_fd: error closing\n");
            return 0;
        }
    }
    if (ft_strncmp(redir_type, "<", ft_strlen(redir_type)) == 0)
        *redir = open(file, O_RDONLY);
    else if(ft_strncmp(redir_type, ">", ft_strlen(redir_type)) == 0)
        *redir = open(file, O_CREAT | O_RDWR, 0777);
    else if (ft_strncmp(redir_type, ">>", ft_strlen(redir_type)) == 0)
        *redir = open(file, O_CREAT | O_RDWR | O_APPEND, 0777);
    return 1;
}

 /*
 **  fills t_parsed_data struct with redirections data
 ** it can return -1 if malloc errors, 0 if close() errors in redir_fd()
 ** or 1 if everything is okay (open () failing also return 1, because it will
 ** be handled in execution)
 ** auxiliary to parse_redir()
 */
int handle_redir(char *redir, char *file, t_parsed_data *parsed_data)
{
    t_list *node;

    node = NULL;
    if (ft_strncmp(redir, "<", ft_strlen(redir)) == 0)
        return redir_fd(&(parsed_data->simple_in_redir), file, "<");

    else if (ft_strncmp(redir, ">", ft_strlen(redir)) == 0)
        return redir_fd(&(parsed_data->simple_out_redir), file, ">");

    else if (ft_strncmp(redir, ">>", ft_strlen(redir)) == 0)
        return redir_fd(&(parsed_data->append), file, ">>");

    else if (ft_strncmp(redir, "<<", ft_strlen(redir)) == 0)
    {
        node = malloc(sizeof(t_list));
        if (node == NULL)
            return -1;
        node->content = ft_strdup(file);
        node->next = NULL;
        ft_lstadd_back(&(parsed_data->here_doc), node);
    }
    return 1;
}

 /*
 **  Takes the original segment, fills the struct with redirection data
 **  and fills a copy of char **segment with modified data to ignore
 **  already parsed data
 */
 char **parse_redir(t_parsed_data *parsed_data, char **split_space)
  {
    int i;
    int sentinel;
    char **cpy_segment;
    
    i = 0;
    cpy_segment = alloc_cpy_segment(split_space);
    if (cpy_segment == NULL)
        return NULL;
    sentinel =  mod_cpy_segment(cpy_segment, i, parsed_data, split_space);
    if (sentinel == -1)
    {
        free(parsed_data->here_doc);
        free_matrix(cpy_segment);
        return NULL;
    }
     return cpy_segment;
 }



 /*
 **  iterates over cpy_segment and returns a new array
 ** where elements with value "1" will be copied
 ** auxiliary to parse_cmd()
 */
 char **cmd_arr(char **cpy_segment)
 {
	int i;
	int count;
	char **cmd;
	
	i = 0;
	count = 0;
	while (cpy_segment[i] != NULL)
	{
		if (ft_strncmp(cpy_segment[i], "1", ft_strlen(cpy_segment[i])) == 0)
			count++;
		i++;
	}
    if (count == 0)
    {
        free_matrix(cpy_segment);
        return NULL;
    }
    cmd = malloc((count + 1) * sizeof(char *));
	if (cmd == NULL)
    {
        free_matrix(cpy_segment);
        return NULL;
    }
	cmd[count] = NULL;
    return cmd;
 }

int fill_cmd_and_args(int i, int j, t_parsed_data *node, char **cmd) 
{
    while (cmd[i] != NULL)
        remove_quotes(cmd[i++]);
    node->args = malloc(i * sizeof(char*));
    if (node->args == NULL) 
        return 0;
    i = 0;
    node->cmd = ft_strdup(cmd[i++]);
    if (node->cmd == NULL) 
    {
        free(node->args);
        return 0;
    }
    while (cmd[i] != NULL)
    {
        node->args[j] = ft_strdup(cmd[i++]);
        if (node->args[j] == NULL)
         {
            free(node->cmd);
            free_matrix(node->args);
            return 0;
        }
        j++;
    }
    node->args[j] = NULL;
    return 1;
}

char *path_is_exec(t_parsed_data *node, char **env_value )
{
	char	*path_cmd;
	char	*end;

	end = ft_strjoin("/", node->cmd);
	if (end == NULL)
		return (NULL);
	while (*env_value++ != NULL)
	{
		path_cmd = ft_strjoin(*env_value, end);
		if (path_cmd == NULL)
		{
			free(end);
			return (NULL);
		}
		if (access(path_cmd, X_OK) == 0)
		{
			free(end);
			return (path_cmd);
		}
		free(path_cmd);
	}
	free(end);
    //add printferror NO_CMD_PATH
	return (NULL);
}

char    **extract_path(t_sh_data *sh)
{
    t_env *current;
    char *to_split;
    char **path;
    
    current = sh->env_header;
    while (current != NULL)
    {
        if (ft_strncmp(current->env_name, "PATH", ft_strlen(current->env_name)) == 0)
        {
           to_split = current->env_value;
           break;
        }
        current = current->next;
    }
    path = ft_split(to_split, ':');
    return path;
}


int fill_path(t_sh_data *sh, t_parsed_data *node)
{
    const char *builtin[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
    int i;
    char **env_path;
    char *path;

    i = 0;
    while(builtin[i] != NULL)
    {
        if (ft_strncmp(node->cmd, builtin[i], ft_strlen(node->cmd)) == 0)
        {
            node->path = node->cmd;
            return 1;
        }
        i++;
    }
    env_path = extract_path(sh);
    if (env_path == NULL)
        return 0;
    path = path_is_exec(node, env_path);
    free_matrix(env_path);
    if (path == NULL) //path can be null because malloc failure or because NO_CMD_PATH
        return 0;
    node->path = path;
    return 1;
}

 /*
 **  
 **  @param1: char **cpy_segment is of size char **segment and is
                           filled with values "0" (if redir data) and "1" (if cmd + args)
                        
 **
 */
 int parse_cmd_and_path(t_sh_data *sh, t_parsed_data *node, char **segment, char **cpy_segment)
 {
    int i;
    int j;
    char **cmd;
    
    i = 0;
    j = 0;
    cmd = cmd_arr(cpy_segment);
    if (cmd == NULL)
        return 0;
    while(segment[i] != NULL)
    {
        if (ft_strncmp(cpy_segment[i], "1", ft_strlen(cpy_segment[i])) == 0)
            cmd[j++] = ft_strdup(segment[i]);
        i++;
    }
    if (fill_cmd_and_args(0, 0, node, cmd) == 0 || fill_path(sh, node) == 0)
    {
        free_matrix(cmd);
        return 0;
    }
	free_matrix(cpy_segment);
	free_matrix(cmd);
    return 1;
 }

