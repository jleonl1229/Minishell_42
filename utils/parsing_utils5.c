/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:25:13 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/09/05 18:28:11 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**  gets the PATH env_var from the env_vars linked list
**  and splits it into a char **
*/
char	**extract_path(t_sh_data *sh)
{
	t_env	*current;
	char	*to_split;
	char	**path;

	current = sh->env_header;
	while (current != NULL)
	{
		if (ft_strncmp(current->env_name, "PATH",
				ft_strlen(current->env_name)) == 0)
		{
			to_split = current->env_value;
			break ;
		}
		current = current->next;
	}
	path = ft_split(to_split, ':');
	if (path == NULL)
		free_matrix(sh->parsed_header->cmd);
	return (path);
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
 int	parse_cmd_and_path(t_sh_data *sh, t_parsed_data *node,
 	char **segment, char **cpy_segment)
 {
    int i;
    int j;
    t_result cmd;
    
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