/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:56:20 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/09/04 18:08:25 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** auxiliary to env_parse()
*/
int	env_quotes(char c, int *single_q, int *double_q, int *j)
{
	if (c == '\"' && *single_q == 0)
	{
		*double_q = !*double_q;
		(*j)++;
		return (1);
	}
	else if (c == '\'' && *double_q == 0)
	{
		*single_q = !*single_q;
		(*j)++;
		return (1);
	}
	return (0);
}

/*
**	returns the value of an environment variable if its name has been found
**	returns empty string if no var_name found or no value has been assigned.
**	ft_strdup failure will be handled in the calling func
**	the flag parameter is used to know if char *var_name needs to be freed or not
**	auxiliary to env_parse()
*/
char	*find_env_pair(t_env *head, char *var_name)
{
	t_env	*current;

	current = head;
	while (current != NULL)
	{
		if (ft_strncmp(current->env_name, var_name, ft_strlen(var_name)) == 0
			&& ft_strlen(current->env_name) == ft_strlen(var_name))
		{
			//free(var_name);
			if (current->env_value != NULL)
				return (ft_strdup(current->env_value));
			else
				return (ft_strdup("\"\""));
		}
		current = current->next;
	}
	return (ft_strdup("\"\""));
}

/*
**	var_content == NULL -> unassigned var
*	ft_strlen(var_content) == 0 -> empty string
*/
t_env	*env_add_value(t_env *new_node, char *var_content)
{
	if (var_content == NULL)
		new_node->env_value = NULL;
	else if (ft_strlen(var_content) == 0)
	{
		new_node->env_value = ft_strdup("");
		{
			if (new_node->env_value == NULL)
			{
				free(new_node->env_name);
				free(new_node);
				return (NULL);
			}
		}
	}
	else
	{
		new_node->env_value = ft_strdup(var_content);
		if (new_node->env_value == NULL)
		{
			free(new_node->env_name);
			free(new_node);
			return (NULL);
		}
	}
	return (new_node);
}

t_env	*env_create_node(char *var_name, char *var_content)
{
	t_env	*new_node;

	new_node = malloc(sizeof(struct s_env));
	if (new_node == NULL)
		return (NULL);
	new_node->env_name = ft_strdup(var_name);
	if (new_node->env_name == NULL)
	{
		free(new_node);
		return (NULL);
	}
	new_node = env_add_value(new_node, var_content);
	if (new_node == NULL)
		return (NULL);
	new_node->next = NULL;
	return (new_node);
}

//adds node to the bottom of the list
void	env_add_node(t_env **header, t_env *new_node)
{
	t_env	*temp;

	if (header == NULL || new_node == NULL)
		return ;
	if (*header == NULL)
	{
		*header = new_node;
		return ;
	}
	temp = *header;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
}
