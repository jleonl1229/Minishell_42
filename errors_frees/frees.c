/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:29:22 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/09/05 16:34:57 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**free_matrix(char **pointer)
{
	int	i;

	i = 0;
	if (pointer == NULL)
		return (NULL);
	while (pointer[i] != NULL)
	{
		free(pointer[i]);
		pointer[i] = NULL;
		++i;
	}
	free(pointer);
	pointer = NULL;
	return (NULL);
}

void	free_tlist(t_list *header)
{
	t_list	*temp;

	if (header == NULL)
		return ;
	while (header != NULL)
	{
		temp = header->next;
		free(header->content);
		free(header);
		header = temp;
	}
}

void	free_env_list(t_env *head)
{
	t_env	*current;
	t_env	*next_node;

	current = head;
	while (current != NULL)
	{
		next_node = current->next;
		free(current->env_name);
		free(current->env_value);
		free(current);
		current = next_node;
	}
}

/*
**  frees every element in t_parsed_struct
**  to be called at the end of the loop iteration,
**  before parsing the next user prompt
*/
void	free_parsing_list(t_sh_data **sh)
{
	t_parsed_data	*current;
	t_parsed_data	*next_node;

	current = (*sh)->parsed_header;
	while (current != NULL)
	{
		next_node = current->next;
		free_matrix(current->cmd);
		free(current->path);
		free(current);
		current = next_node;
	}
}

/*
**  function called when dup_env(), bad_initial_char() or bad_final_char() error
*/
void	pre_parse_cleanup(t_sh_data **sh, t_env *header, char **org)
{
	if (org != NULL)
		free_matrix(org);
	if ((*sh)->env_header != NULL)
		free_env_list((*sh)->env_header);
	else
		free_env_list(header);
	if ((*sh)->prev_line != NULL)
		free((*sh)->prev_line);
	free(*sh);
	exit(1);
}
