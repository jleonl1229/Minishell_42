/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:06:30 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/09/06 15:15:47 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	schar(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/*
**	returns the length of the new_line, which is line's length
**	+ the spaces around the special chars, ignoring special
**	chars inside quotes
*/
int	new_line_length(char *line, int len, int in_dquote, int in_squote)
{
	int	i;
	int	new_len;

	i = 0;
	new_len = 0;
	while (i < len)
	{
		if (line[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (line[i] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		if (!in_squote && !in_dquote && schar(line[i]))
		{
			if (i > 0 && line[i - 1] != ' ' && !schar(line[i -1]))
				new_len++;
			new_len++;
			if (i < len - 1 && line[i + 1] != ' '
				&& !schar(line[i + 1]))
				new_len++;
		}
		else
			new_len++;
		i++;
	}
	return (new_len);
}

void	fill_new_line(char **new_line, char *l, int in_squote, int in_dquote)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	while (i < ft_strlen(l))
	{
		if (l[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (l[i] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		if (!in_squote && !in_dquote && schar(l[i]))
		{
			if (i > 0 && l[i - 1] != ' ' && !schar(l[i -1]))
				(*new_line)[j++] = ' ';
			(*new_line)[j++] = l[i];
			if (i < ft_strlen(l) - 1 && l[i + 1] != ' ' && !schar(l[i +1]))
				(*new_line)[j++] = ' ';
		}
		else
			(*new_line)[j++] = l[i];
		i++;
	}
	(*new_line)[j] = '\0';
}

/*
** from "<cat<<cat|cat" to " < cat << cat | cat". Adds spaces around
**  special chars.
**  new_line is saved in the t_sh_data struct
**  I forgot why is this useful
*/
void	add_space(t_sh_data *sh)
{
	int		new_len;
	char	*new_line;
	int		len;

	len = ft_strlen(sh->prev_line);
	new_len = new_line_length(sh->prev_line, len, 0, 0);
	new_line = malloc(new_len + 1);
	if (new_line == NULL)
		pre_parse_cleanup (&sh, 0, 0);
	fill_new_line(&new_line, sh->prev_line, 0, 0);
	sh->new_line = ft_strdup(new_line);
	if (sh->new_line == NULL)
	{
		free(new_line);
		pre_parse_cleanup (&sh, 0, 0);
	}
	free(new_line);
}

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
