/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:44:20 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/09/06 13:22:17 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**  iterates over cpy_segment and returns a new array
**	where elements with value "1" will be copied.
**	using a struct to differentiate return values of NULL between malloc error 
**	and count == 0
** auxiliary to parse_cmd_and_path()
*/
t_result	cmd_arr(char **cpy_segment, int i, int count)
{
	t_result	res;

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
		return (res);
	}
	res.str_arr = malloc((count + 1) * sizeof(char *));
	if (res.str_arr == NULL)
	{
		free_matrix(cpy_segment);
		res.error_code = 2;
		return (res);
	}
	res.str_arr[count] = NULL;
	res.error_code = 0;
	return (res);
}

/*
**  checks if inputed command has a valid absolute path to an executable
**  the stat() function helps differentiate executables from directories.
**  previously had a bug where "/home/user" would return true, even if directory
**  about the stat function:
**      the struct holds info about the file (type, permissions, etc.)
**      path_stat is populated with this information
**      S_ISREG_ checks if file is regular file (not a directory or special file)
**  returns 1 if there is an executable, 0 otherwise
*/
int	is_absolute_path(t_parsed_data *node)
{
	struct stat	path_stat;

	if (node->cmd[0][0] == '/' || (node->cmd[0][0] == '.' &&
	(node->cmd[0][1] == '/' || node->cmd[0][1] == '.')))
	{
		if (stat(node->cmd[0], &path_stat) == 0)
		{
			if (S_ISREG(path_stat.st_mode) && access(node->cmd[0], X_OK) == 0)
			{
				node->path = ft_strdup(node->cmd[0]);
				return (1);
			}
		}
	}
	return (0);
}
