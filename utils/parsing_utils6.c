/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:04:40 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/09/06 15:33:29 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	if split_spaces has been ["echo", "hello", ">", "out", NULL]
**  char **cmd will be ["echo", "hello", NULL]
**  for each element quotes are removed and the cmd element from the node struct
** is filled (cmd[0] will be the command and cmd++ will be the args)
*/
int	fill_cmd_args(int i, t_parsed_data *node, char **cmd)
{
	while (cmd[i] != NULL)
		remove_quotes(cmd[i++]);
	node->cmd = malloc((i + 1) * sizeof (char *));
	if (node->cmd == NULL)
		return (0);
	i = 0;
	while (cmd[i] != NULL)
	{
		node->cmd[i] = ft_strdup(cmd[i]);
		if (node->cmd[i] == NULL)
		{
			free_matrix(node->cmd);
			return (0);
		}
		i++;
	}
	node->cmd[i] = NULL;
	return (1);
}

/*
**  if no path has been found for cmd, it returns NULL and program keeps going
**  as the execution part will be responsible for printing a "no cmd path error"
**  it returns -1 when there's been a malloc failure.
*/
char	*path_is_exec(t_parsed_data *node, char **env_value, char *end)
{
	char	*path_cmd;

	if (is_absolute_path(node) == 1 || ft_strlen(node->cmd[0]) == 0)
		return (NULL);
	printf("not absolute\n");
	end = ft_strjoin("/", node->cmd[0]);
	printf("end is: %s\n", end);
	if (end == NULL)
		return ((char *) -1);
	while (*env_value != NULL)
	{
		path_cmd = ft_strjoin(*env_value, end);
		if (path_cmd == NULL)
		{
			free(end);
			return ((char *) - 1);
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
int	fill_path(t_sh_data *sh, t_parsed_data *node)
{
	char	**env_path;
	char	*path;

	if (is_builtin(node->cmd[0]) == 1)
	{
		node->path = ft_strdup(node->cmd[0]);
		return (1);
	}
	if (env_checker(sh->env, &sh) == 2)
		return (3);
	env_path = extract_path(sh);
	if (env_path == NULL)
		return (0);
	path = path_is_exec(node, env_path, NULL);
	printf("node->path is: %s\n", path);
	free_matrix(env_path);
	if (node->path != NULL)
		return (1);
	if (path == (char *) -1)
	{
		free_matrix(node->cmd);
		return (0);
	}
	node->path = path;
	return (1);
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
	int			i;
	int			j;
	t_result	cmd;

	i = 0;
	j = 0;
	cmd = cmd_arr(cpy_segment, 0, 0);
	if (cmd.error_code == 1)
		return (0);
	else if (cmd.error_code == 2)
		return (-1);
	while (segment[i] != NULL)
	{
		if (ft_strncmp(cpy_segment[i], "1", ft_strlen(cpy_segment[i])) == 0)
			cmd.str_arr[j++] = ft_strdup(segment[i]);
		i++;
	}
	free_matrix(cpy_segment);
	if (fill_cmd_args(0, node, cmd.str_arr) == 0 || fill_path(sh, node) == 0)
	{
		free_matrix(cmd.str_arr);
		return (-1);
	}
	free_matrix(cmd.str_arr);
	return (1);
}
