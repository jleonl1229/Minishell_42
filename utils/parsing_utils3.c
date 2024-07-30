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
 **  fills t_parsed_data struct with redirections data
 ** auxiliary to parse_redir()
 */
 int handle_redir(char *redir, char *file, t_parsed_data *parsed_data)
 {
    if (ft_strncmp(redir, "<", ft_strlen(redir)) == 0)
    {
        free(parsed_data->simple_in_redir);
        if ((parsed_data->simple_in_redir = ft_strdup(file)) == NULL)
            return 0;
    }
    else if (ft_strncmp(redir, ">", ft_strlen(redir)) == 0)
    {
        free(parsed_data->simple_out_redir);
        if((parsed_data->simple_out_redir = ft_strdup(file)) == NULL)
            return 0;
    }
    else if (ft_strncmp(redir, ">>", ft_strlen(redir)) == 0)
    {
        free(parsed_data->append);
        if ((parsed_data->append = ft_strdup(file)) == NULL)
            return 0;
    }
    else if (ft_strncmp(redir, "<<", ft_strlen(redir)) == 0)
    {
        free(parsed_data->here_doc);
        if ((parsed_data->here_doc = ft_strdup(file)) == NULL)
            return 0;
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
        free(parsed_data->simple_in_redir);
        free(parsed_data->simple_out_redir);
        free(parsed_data->append);
        free(parsed_data->here_doc);
        free_matrix(cpy_segment);
        return NULL;
    }
     return cpy_segment;
 }



 /*
 **  iterates over cpy_segment and returns a new array
 ** where elements with value "1" will be copied
 ** auxiliary of parse_cmd()
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
        return NULL;
    cmd = malloc((count + 1) * sizeof(char *));
	if (cmd == NULL)
		exit(1);
	cmd[count] = NULL;
    return cmd;
 }

 /*
 **  
 **  @param1: char **cpy_segment is of size char **segment and is
                           filled with values "0" (if redir data) and "1" (if cmd + args)
                        
 **
 */
 void parse_cmd(t_parsed_data *node, char **segment, char **cpy_segment)
 {
     int i;
     int j;
     char **cmd;

     i = 0;
     j = 0;
     cmd = cmd_arr(cpy_segment);
     if (cmd == NULL)
     {
        free_matrix(cpy_segment);
        return;
     }
     while(segment[i] != NULL)
     {
         if (ft_strncmp(cpy_segment[i], "1", ft_strlen(cpy_segment[i])) == 0)
             cmd[j++] = ft_strdup(segment[i]);
         i++;
     }
     i = 0;
     while (cmd[i] != NULL)
		remove_quotes(cmd[i++]);
     node->args = malloc(i * sizeof(char*));
     i = 0;
     node->cmd = ft_strdup(cmd[i++]);
     j = 0;
     while(cmd[i] != NULL)
         node->args[j++]= ft_strdup(cmd[i++]);
     node->args[j] = NULL;
	free_matrix(cpy_segment);
	free_matrix(cmd);
 }
