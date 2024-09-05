/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:27:46 by jleon-la          #+#    #+#             */
/*   Updated: 2024/09/05 16:55:06 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*free_node_unset(t_env *node)
{
	t_env	*temp;

	temp = node;
	node = node->next;
	free(temp->env_name);
	free(temp->env_value);
	free(temp);
	return (node);
}

/*
**	one for the linked list
**	set = 0 ->header points to removable env_var
*/
void	unset_remove_tenv(char *arg, t_env **env, int set)
{
	t_env	*current;
	t_env	*previous;

	if (set == 0)
	{
		*env = free_node_unset(*env);
		return ;
	}
	previous = *env;
	current = (*env)->next;
	while (current != NULL)
	{
		if (ft_strncmp(current->env_name, arg, ft_strlen(arg)) == 0
			&& ft_strlen(current->env_name) == ft_strlen(arg))
		{
			previous->next = free_node_unset(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

//one for the char **
void	unset_remove_shenv(char **env, int set)
{
	int	i;

	free(env[set]);
	i = set;
	while (env[i + 1] != NULL)
	{
		env[i] = env[i + 1];
		i++;
	}
	env[i] = NULL;
}

/*
**  as we have 2 data structures containing the env_vars
**  we have to delete from both data structures
**
**  the unset command in my shell implementation doesn't throw errors for invalid
**  identifiers, I need to check how it behaves in 42
**  invalid usages of unset:
**      1. unset without arguments (no error)      
**      2. unset $AAA won't do anything (not throwing error)
**      3. 
*/

int	mini_unset(t_parsed_data *header, t_sh_data *sh)
{
	char	**cmd;
	char	*arg;
	int		set;

	cmd = header->cmd;
	if (cmd[1] == NULL)
		return (0);
	while (*(++cmd) != NULL)
	{
		arg = *cmd;
		set = is_var_set(sh->env_header, arg);
		if (set == -1)
			return (0);
		if (is_simple_cmd(sh) == 1)
		{
			unset_remove_tenv(arg, &(sh->env_header), set);
			unset_remove_shenv(sh->env, set);
		}
	}
	return (0);
}
