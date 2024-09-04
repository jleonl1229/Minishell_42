/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:44:20 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/09/04 19:40:01 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// adds node to the bottom of the linked list
void	parse_add_node(t_parsed_data **head, t_parsed_data *new_node)
{
	t_parsed_data	*current;

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
char	**alloc_cpy_segment(char **segment)
{
	int		size;
	char	**cpy_segment;

	size = 0;
	while (segment[size] != NULL)
		size++;
	cpy_segment = (char **)malloc((size + 1) * sizeof(char *));
	if (cpy_segment == NULL)
		return (NULL);
	return (cpy_segment);
}

/*
**  fills the elements in cpy_segment with "0"s to signal further functions
**  that we're done with these elements.
**  @param: char ***cpy_segment is the address of the char ** created
**                   by alloc_cpy_segment()
** auxiliary to parse_redir()
*/
int	mod_cpy_segment(char **cpy_segment, int i, t_parsed_data *parsed_data,
					char **segment)
{
	while (segment[i] != NULL)
	{
		if (ft_strncmp(segment[i], "<", ft_strlen(segment[i])) == 0
			|| ft_strncmp(segment[i], ">", ft_strlen(segment[i])) == 0
			|| ft_strncmp(segment[i], "<<", ft_strlen(segment[i])) == 0
			|| ft_strncmp(segment[i], ">>", ft_strlen(segment[i])) == 0)
		{
			if (handle_redir(segment[i], segment[i + 1], parsed_data) != 1)
			{
				cpy_segment[i] = NULL;
				return (-1);
			}
			cpy_segment[i] = ft_strdup("0");
			cpy_segment[i + 1] = ft_strdup("0");
			if (cpy_segment[i] == NULL || cpy_segment[i + 1] == NULL)
				return (-1);
			i += 2;
		}
		else
		{
			if ((cpy_segment[i++] = ft_strdup("1")) == NULL)
				return -1;			
		}
	}
	cpy_segment[i] = NULL;
	return (0);
 }

/*
**  simple_in_redir initialized to -2.
**  if return 0, terminate current command but don't exit program, 
**  keep listening for new commands
** auxiliary to handle_redir()
*/
int redir_fd(t_parsed_data *parsed_data, int *redir, char *file, char *redir_type)
{
    int fd;

    fd = 0;
    if (*redir == -1)
        return (1);
    if (*redir != -2 && *redir != 988)
    {
        fd = close(*redir);
        if (fd == -1)
            return (printf("redir_fd(): close() function error\n"));
    }
    if (ft_strncmp(redir_type, "<", ft_strlen(redir_type)) == 0)
        *redir = open(file, O_RDONLY);
    else if(ft_strncmp(redir_type, ">", ft_strlen(redir_type)) == 0)
    {
        *redir = open(file, O_CREAT | O_RDWR | O_TRUNC, 0777);
        parsed_data->last_fd = *redir;
    }
    else if (ft_strncmp(redir_type, ">>", ft_strlen(redir_type)) == 0)
    {
        *redir = open(file, O_CREAT | O_RDWR | O_APPEND, 0777);
        parsed_data->last_fd = *redir;
    }
    return 1;
}

 /*
 ** fills t_parsed_data struct with redirections data
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
        return redir_fd(parsed_data, &(parsed_data->simple_in_redir), file, "<");
    else if (ft_strncmp(redir, ">", ft_strlen(redir)) == 0)
        return redir_fd(parsed_data, &(parsed_data->last_fd), file, ">");
    else if (ft_strncmp(redir, ">>", ft_strlen(redir)) == 0)
        return redir_fd(parsed_data, &(parsed_data->last_fd), file, ">>");
    else if (ft_strncmp(redir, "<<", ft_strlen(redir)) == 0)
    {
        node = malloc(sizeof(t_list));
        if (node == NULL || (node->content = ft_strdup(file)) == NULL)
            return printf("handle_redir(): malloc failure");
        node->next = NULL;
        ft_lstadd_back(&(parsed_data->here_doc), node);
        if (parsed_data->simple_in_redir != -1)
        {
            if (parsed_data->simple_in_redir != -2)
                close(parsed_data->simple_in_redir);
            parsed_data->simple_in_redir = 988;
        }
    }
    return 1;
}

 /*
 **  Takes the original segment, fills the struct with redirection data
 **  and fills a copy of char **segment with modified data to ignore
 **   the already parsed data
 ** 988 indicates infile is from hdoc
 */
 result parse_redir(t_parsed_data *parsed_data, char **split_space, int i, int sentinel)
{
    result res;
    int new_fd;
    
    res.str_arr = alloc_cpy_segment(split_space);
    if (res.str_arr == NULL)
    {
        res.error_code = 2;
        return res;
    }
    sentinel =  mod_cpy_segment(res.str_arr, i, parsed_data, split_space);
    if (sentinel == -1)
        return (free_parse_redir(res, sentinel, parsed_data));
    if (parsed_data->here_doc != NULL)
    {
        new_fd = heredoc_to_infile(parsed_data->here_doc);
        if (new_fd == -1 || new_fd == -2)
            return (free_parse_redir(res, new_fd, parsed_data));  
        if (parsed_data->simple_in_redir != -1 && parsed_data->simple_in_redir == 988)
            parsed_data->simple_in_redir = new_fd;
        else
            close(new_fd); //unprotected
        free_tlist(parsed_data->here_doc);
    }
    res.error_code = 0;
    return res;
}


 /*
 **  iterates over cpy_segment and returns a new array
 ** where elements with value "1" will be copied.
 ** using a struct to differentiate return values of NULL between malloc error and count == 0
 ** auxiliary to parse_cmd_and_path()
 */
 result cmd_arr(char **cpy_segment, int i, int count)
 {
    result res;

	while (cpy_segment[i] != NULL)
	{
		if (ft_strncmp(cpy_segment[i], "1", ft_strlen(cpy_segment[i])) == 0)
			count++;
		i++;
	}
    if (count == 0)
    {
        free_matrix(cpy_segment);
        res.error_code = 1;
        res.str_arr = NULL;
        return res;
    }
    res.str_arr = malloc((count + 1) * sizeof(char *)); 
	if (res.str_arr == NULL)
    {
        free_matrix(cpy_segment);
        res.error_code = 2;
        return res; 
    }
	res.str_arr[count] = NULL;
    res.error_code = 0;
    return res;
 }


/*
**  At this point and if split_spaces has been ["echo", "hello", ">", "out", NULL]
**  char **cmd will be ["echo", "hello", NULL]
**  for each element quotes are removed and the the cmd element from the parsed node struct
** is filled (cmd[0] will be the command and cmd++ will be the args)
*/
int fill_cmd_and_args(int i, t_parsed_data *node, char **cmd) 
{
    while (cmd[i] != NULL)
        remove_quotes(cmd[i++]);
    node->cmd = malloc((i +1)* sizeof(char*));
    if (node->cmd == NULL) 
        return 0;
    i = 0;
    while (cmd[i] != NULL)
    {
        node->cmd[i] = ft_strdup(cmd[i]);
        if (node->cmd[i] == NULL)
         {
            free_matrix(node->cmd);
            return 0;
        }
        i++;
    }
    node->cmd[i] = NULL;
    return 1;
}

/*
**  checks if inputed command has a valid absolute path to an executable
**  the stat() function helps differentiate executables from directories.
**  previously had a bug where "/home/user" would return true, even if it's a directory
**  about the stat function:
**      the struct holds info about the file (type, permissions, etc.)
**      path_stat is populated with this information
**      S_ISREG_ checks if file is a regular file (not a directory or special file)
**  returns 1 if there is an executable, 0 otherwise
*/
int is_absolute_path(t_parsed_data *node)
{
    struct stat path_stat;

    if (node->cmd[0][0] == '/' || (node->cmd[0][0] == '.' && 
    (node->cmd[0][1] == '/' || node->cmd[0][1] == '.')))
    {
        if (stat(node->cmd[0], &path_stat) == 0)
        {
            if (S_ISREG(path_stat.st_mode) && access(node->cmd[0], X_OK) == 0)
            {
                node->path = ft_strdup(node->cmd[0]);
                return 1;
            }
        }
    }
    return 0;

}

/*
**  if no path has been found for cmd, it returns NULL and program keeps going
**  as the execution part will be responsible for printing a "no cmd path error"
**  it returns -1 when there's been a malloc failure.
*/
char *path_is_exec(t_parsed_data *node, char **env_value, char *end)
{
	char	*path_cmd;

    if (is_absolute_path(node) == 1||ft_strlen(node->cmd[0]) == 0)
        return (NULL);
    end = ft_strjoin("/", node->cmd[0]);
	if (end == NULL)
		return (char *) -1;
	while (*env_value != NULL)
	{
		path_cmd = ft_strjoin(*env_value, end);
		if (path_cmd == NULL)
		{
			free(end);
			return (char *) -1;
		}
		if (access(path_cmd, X_OK) == 0)
		{
			free(end);
			return (path_cmd);
		}
		free(path_cmd);
        env_value++;
	}
	free(end);
	return (NULL);
}

/*
**  gets the PATH env_var from the env_vars linked list
**  and splits it into a char **
*/
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
    if (path == NULL)
        free_matrix(sh->parsed_header->cmd);
    return path;
}

/*
**  fills the path to executable data of the t_parsed_node.
**  if the cmd is a builtin cmd it fills the path with the builtin name
**  returns 1 if no error, 0 if malloc failure
*/
int fill_path(t_sh_data *sh, t_parsed_data *node)
{
    char **env_path;
    char *path;

    if (is_builtin(node->cmd[0]) == 1)
    {
        node->path = ft_strdup(node->cmd[0]); //unprotected
        return 1;
    }
    env_path = extract_path(sh);
    if (env_path == NULL)
        return 0;
    path = path_is_exec(node, env_path, NULL);
    free_matrix(env_path);
    if(node->path != NULL) //meaning that path is absolute
        return 1;
    if (path == (char *) -1) //malloc failure
    {
        free_matrix(node->cmd);
        return 0;
    }
    node->path = path;
    return 1;
}

 /*
 **  params:
 **     char **segment -> ["echo", "hello", ">", "outfile.txt", NULL]
 **     char **cpy_segment-> ["1", "1", "0", "0", NULL]                        
 ** cmd_arr() -> creates a new arr where cmd + args will be stored
 ** fill_cmd_and_args() -> fills the t_parsed_node struct with cmd + args data
 ** fill_path() -> adds the path to the executable to the t_parsed_node
 ** cmd.error_code 1 --> count 0, meaning there's no command to parse
 ** cmd.error_code 2 --> malloc failure
 */
 int parse_cmd_and_path(t_sh_data *sh, t_parsed_data *node, char **segment, char **cpy_segment)
 {
    int i;
    int j;
    result cmd;
    
    i = 0;
    j = 0;
    cmd = cmd_arr(cpy_segment, 0, 0);
    if (cmd.error_code == 1)
        return 0;
    else if (cmd.error_code == 2)
        return -1;
    while(segment[i] != NULL)
    {
        if (ft_strncmp(cpy_segment[i], "1", ft_strlen(cpy_segment[i])) == 0)
            cmd.str_arr[j++] = ft_strdup(segment[i]);
        i++;
    }
    free_matrix(cpy_segment);
    if (fill_cmd_and_args(0, node, cmd.str_arr) == 0 || fill_path(sh, node) == 0)
    {
        free_matrix(cmd.str_arr);
        return -1;
    }
	free_matrix(cmd.str_arr);
    return 1;
 }

