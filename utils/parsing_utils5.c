/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:25:13 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/09/06 13:01:00 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			cpy_segment[i++] = ft_strdup("1");
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
int	redir_fd(t_parsed_data *parsed_data, int *redir,
	char *file, char *redir_type)
{
	int	fd;

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
	else if (ft_strncmp(redir_type, ">", ft_strlen(redir_type)) == 0)
	{
		*redir = open(file, O_CREAT | O_RDWR | O_TRUNC, 0777);
		parsed_data->last_fd = *redir;
	}
	else if (ft_strncmp(redir_type, ">>", ft_strlen(redir_type)) == 0)
	{
		*redir = open(file, O_CREAT | O_RDWR | O_APPEND, 0777);
		parsed_data->last_fd = *redir;
	}
	return (1);
}

/*
** fills t_parsed_data struct with redirections data
** it can return -1 if malloc errors, 0 if close() errors in redir_fd()
** or 1 if everything is okay (open () failing also return 1, because it will
** be handled in execution)
** auxiliary to parse_redir()
*/
int	handle_redir(char *redir, char *file, t_parsed_data *p_data)
{
	t_list	*node;

	node = NULL;
	if (ft_strncmp(redir, "<", ft_strlen(redir)) == 0)
		return (redir_fd(p_data, &(p_data->simple_in_redir), file, "<"));
	else if (ft_strncmp(redir, ">", ft_strlen(redir)) == 0)
		return (redir_fd(p_data, &(p_data->last_fd), file, ">"));
	else if (ft_strncmp(redir, ">>", ft_strlen(redir)) == 0)
		return (redir_fd(p_data, &(p_data->last_fd), file, ">>"));
	else if (ft_strncmp(redir, "<<", ft_strlen(redir)) == 0)
	{
		node = malloc(sizeof(t_list));
		node->content = ft_strdup(file);
		node->next = NULL;
		ft_lstadd_back(&(p_data->here_doc), node);
		if (p_data->simple_in_redir != -1)
		{
			if (p_data->simple_in_redir != -2)
				close(p_data->simple_in_redir);
			p_data->simple_in_redir = 988;
		}
	}
	return (1);
}

/*
**  Takes the original segment, fills the struct with redirection data
**  and fills a copy of char **segment with modified data to ignore
**   the already parsed data
** 988 indicates infile is from hdoc
*/
t_result	parse_redir(t_parsed_data *p_data, char **split_space,
	int i, int sentinel)
{
	t_result	res;
	int			new_fd;

	res.str_arr = alloc_cpy_segment(split_space);
	if (res.str_arr == NULL)
	{
		res.error_code = 2;
		return (res);
	}
	sentinel = mod_cpy_segment(res.str_arr, i, p_data, split_space);
	if (sentinel == -1)
		return (free_parse_redir(res, sentinel, p_data));
	if (p_data->here_doc != NULL)
	{
		new_fd = heredoc_to_infile(p_data->here_doc);
		if (new_fd == -1 || new_fd == -2)
			return (free_parse_redir(res, new_fd, p_data));
		if (p_data->simple_in_redir != -1 && p_data->simple_in_redir == 988)
			p_data->simple_in_redir = new_fd;
		else
			close(new_fd);
		free_tlist(p_data->here_doc);
	}
	res.error_code = 0;
	return (res);
}
