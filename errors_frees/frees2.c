/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:29:35 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/09/05 18:15:18 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parsing_cleanup(t_sh_data **sh, char **pipe_segments,
			char **split_space)
{
	free((*sh)->new_line);
	if (pipe_segments != NULL)
		free_matrix(pipe_segments);
	if (split_space != NULL)
		free_matrix(split_space);
	pre_parse_cleanup(sh, 0, 0);
}

void	frees_before_next_ite(char *line, t_sh_data **sh)
{
	free(line);
	free((*sh)->new_line);
	(*sh)->new_line = NULL;
	free_parsing_list(sh);
}

void	free_hdoc_sigint(t_parsed_data *node, t_sh_data *sh,
			char **p_seg, char **splt_sp)
{
	free(node);
	free(sh->new_line);
	free_matrix(p_seg);
	free_matrix(splt_sp);
}

t_result	free_parse_redir(t_result res, int flag, t_parsed_data *parsed_data)
{
	free_tlist(parsed_data->here_doc);
	free_matrix(res.str_arr);
	res.str_arr = NULL;
	if (flag == -1)
		res.error_code = 2;
	else
		res.error_code = 1;
	return (res);
}
