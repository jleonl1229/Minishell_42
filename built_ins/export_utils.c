/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:14:51 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/09/05 17:24:12 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**  checks if var_name is already set as env_var
**  if var_name already exists, returns its node position in the linked list
**  otherwise it returns -1
*/
int	is_var_set(t_env *env, char *cmd)
{
	int	set;

	set = 0;
	while (env != NULL)
	{
		if (ft_strncmp(env->env_name, cmd, ft_strlen(cmd)) == 0
			&& ft_strlen(env->env_name) == ft_strlen(cmd))
			return (set);
		env = env->next;
		set++;
	}
	return (-1);
}

/*
**  Extracts the variable name and value from the cmd
**  The if condition inside the while loop will be true if it's
**  an assigned env_var
**  else it will be unassigned and also be strduped
*/
char	**get_var_data(char *cmd)
{
	char	**env_var;
	int		i;

	i = 0;
	env_var = malloc(sizeof(char *) * 3);
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '=')
		{
			env_var[0] = (char *)malloc(i + 1);
			ft_strlcpy(env_var[0], cmd, i +1);
			env_var[1] = (char *)malloc(ft_strlen(cmd) - ft_strlen(env_var[0]));
			ft_strlcpy(env_var[1], cmd + ft_strlen(env_var[0]) + 1,
				ft_strlen(cmd) - ft_strlen(env_var[0]));
			env_var[2] = NULL;
			return (env_var);
		}
		i++;
	}
	env_var[0] = ft_strdup(cmd);
	env_var[1] = NULL;
	env_var[2] = NULL;
	return (env_var);
}

/*
** a var_name is considered invalid if:
**      1. starts with non-alphabetic or underscore char (digits, quotes, etc.)
**      2. contains a char that is not alphabetic, digit or underscore
*/
int	is_valid_arg_export(char *arg)
{
	int	res;
	int	i;

	res = 1;
	i = 0;
	if (ft_isalpha(arg[0]) != 1 && arg[0] != '_')
	{
		res = 0;
		printf("export: `%s': not a valid identifier\n", arg);
		return (res);
	}
	while (arg[i] != '\0' && arg[i] != '=')
	{
		if (ft_isalnum(arg[i]) != 1 && arg[i] != '_')
		{
			res = 0;
			printf("export: `%s': not a valid identifier\n", arg);
			return (res);
		}
		i++;
	}
	return (res);
}

/*
** swaps name and values of 2 contiguous nodes in a t_env linked list
** auxiliary to sort_lst()
*/
void	swap_nodes(t_env *a, t_env *b)
{
	char	*temp_name;
	char	*temp_value;

	temp_name = a->env_name;
	temp_value = a->env_value;
	a->env_name = b->env_name;
	a->env_value = b->env_value;
	b->env_name = temp_name;
	b->env_value = temp_value;
}

/*
**  sorts environment variables alphabetically by their var_name
**  auxiliary to sort_env()
*/
void	sort_lst(t_env **env)
{
	int		swapped;
	t_env	*current;

	swapped = 1;
	if (*env == NULL)
		return ;
	while (swapped == 1)
	{
		swapped = 0;
		current = *env;
		while (current != NULL && current->next != NULL)
		{
			if (ft_strncmp(current->env_name, current->next->env_name,
					ft_strlen(current->env_name) + 1) > 0)
			{
				swap_nodes(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
	}
}
