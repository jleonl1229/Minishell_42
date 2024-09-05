/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:09:45 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/09/05 17:50:21 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**  split the command line into simple commands
*/
char	**split_by_pipe(char *line, int start, int segment_index, int i)
{
	int		segments;
	char	**result;

	segments = count_segments(line);
	result = malloc((segments + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	while (segment_index < segments)
	{
		if (line[i] == '\'' || line[i] == '"')
			skip_quotes(line, &i);
		if (line[i] == '|' || line[i] == '\0')
		{
			result[segment_index] = malloc((i - start + 1) * sizeof(char));
			if (result[segment_index] == NULL)
				return (free_matrix(result));
			ft_strlcpy(result[segment_index], line + start, i - start + 1);
			segment_index++;
			start = i + 1;
		}
		i++;
	}
	result[segments] = NULL;
	return (result);
}

/*
**  auxiliary to parse_line()
*/
void	parsed_node_init(t_parsed_data *node)
{
	node->path = NULL;
	node->cmd = NULL;
	node->simple_in_redir = -2;
	node ->last_fd = -2;
	node->here_doc = NULL;
	node->next = NULL;
}

/*
**  initializes a new t_parsed_data node and handles functions to fill 
**	the node with data. adds the node to the bottom of the linked list 
**	of t_parsed_data nodes split_space is a pipe_segment (simple command),
**	but each element being splitted by space
**  res.error_code = 1-> SIGINT caught while here_docing
**  res.error_code = 2 -> open(), close() errors or malloc failure
**  if parse_cmd_and_path() == -1 it means there's been a malloc failure
*/
void	parse_line(t_sh_data **sh, t_parsed_data **header, char **split_space,
		char **pipe_segments)
{
	t_parsed_data	*node;
	t_result			res;

	node = (t_parsed_data *)malloc(sizeof(t_parsed_data));
	if (node == NULL)
		parsing_cleanup(sh, pipe_segments, split_space);
	parsed_node_init(node);
	res = parse_redir(node, split_space, 0, 0);
	if (res.error_code == 2)
	{
		free(node);
		parsing_cleanup(sh, pipe_segments, split_space);
	}
	else if (res.error_code == 1)
		return (free_hdoc_sigint(node, *sh, pipe_segments, split_space));
	if (parse_cmd_and_path(*sh, node, split_space, res.str_arr) == -1)
	{
		free(node);
		parsing_cleanup(sh, pipe_segments, split_space);
	}
	parse_add_node(header, node);
}

/*
**  flow:
**  take command line and add spaces to it. split it by pipes(simple commands).
**  take each simple command and split it by space. parse env_var expansions,
**	parse redirs, fill node struct data
*/
t_parsed_data	*parsing(t_sh_data *sh, t_parsed_data *head, int i)
{
	char	**pipe_segments;
	char	**split_space;

	add_space(sh);
	pipe_segments = split_by_pipe(sh->new_line, 0, 0, 0);
	if (pipe_segments == NULL)
		parsing_cleanup(&sh, 0, 0);
	while (pipe_segments[i] != NULL)
	{
		split_space = ft_split_quotes(pipe_segments[i++], ' ');
		if (split_space == NULL)
			parsing_cleanup(&sh, pipe_segments, 0);
		split_space = env_parse (0, 0, split_space, sh);
		if (split_space == NULL)
			parsing_cleanup(&sh, pipe_segments, split_space);
		parse_line(&sh, &head, split_space, pipe_segments);
		if (g_signal == 1)
		{
			g_signal = 0;
			return (NULL);
		}
		free_matrix(split_space);
	}
	free_matrix(pipe_segments);
	return (head);
}
