/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:06:33 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/09/04 18:07:45 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//auxiliary to the cd builtin
char * custom_getenv(t_env *head, const char *name)
{
	t_env *current;

	current = head;
	while (current != NULL)
	{
		if (ft_strncmp(current->env_name, name, ft_strlen(name)) == 0
		&& ft_strlen(current->env_name) == ft_strlen(name))
			return current->env_value;
		current = current->next;
	}
	return NULL;
}

size_t	env_count_char(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (s[count] != c && s[count] != '\0')
		count++;
	return (count);
}

/*
**	3 as malloc size because hardcoding 2 for substr + 1 for NULL
*/
char	**env_split(const char *s, char c)
{
	char	**pointer;
	size_t	substr_length;

	pointer = malloc(sizeof(char *) * 3);
	if (pointer == NULL)
		return (NULL);
	substr_length = env_count_char(s, c);
	pointer[0] = malloc(sizeof(char) * (substr_length + 1));
	if (pointer[0] == NULL)
		return (free_matrix(pointer));
	ft_strlcpy(pointer[0], s, substr_length + 1);
	s += substr_length;
	if (*s == c)
		s++;
	pointer[1] = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (pointer[1] == NULL)
		return (free_matrix(pointer));
	ft_strlcpy(pointer[1], s, ft_strlen(s) + 1);
	pointer[2] = NULL;
	return (pointer);
}
