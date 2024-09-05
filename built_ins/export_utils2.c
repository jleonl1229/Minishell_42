/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:05:53 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/09/05 17:24:19 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**  duplicates the t_env linked list wolding the env_vars
**  used when export without args has been casted, 
**  to create the linked list that will be sorted
*/
t_env	*dup_env(t_env *env)
{
	t_env	*head;
	t_env	*node;

	head = NULL;
	while (env != NULL)
	{
		node = env_create_node(env->env_name, env->env_value);
		if (node == NULL)
			return (NULL);
		env_add_node(&head, node);
		env = env->next;
	}
	return (head);
}

int	is_simple_cmd(t_sh_data *sh)
{
	if (sh->parsed_header->next == NULL)
		return (1);
	return (0);
}

void	add_shenv_var(t_sh_data *sh, char **new_env, char *cmd)
{
	int	i;

	i = 0;
	while (new_env[i] != NULL)
		i++;
	new_env[i] = ft_strdup(cmd);
	if (new_env[i] == NULL)
		sh->env = NULL;
}

/*
** duplicates sh->env
**	if set == -1: +1 for new env_var + 1 for NULL
*/
char	**dup_sh_env(char **env, int set)
{
	char	**new_env;
	int		i;

	i = 0;
	while (env[i] != NULL)
		i++;
	if (set == -1)
		new_env = malloc(sizeof(char *) * (i + 2));
	else
		new_env = malloc(sizeof(char *) * (i + 1));
	if (new_env == NULL)
		return (NULL);
	new_env[i] = NULL;
	if (set == -1)
		new_env[i + 1] = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	free_matrix(env);
	return (new_env);
}

/*

**  int set: the position in the char ** where the existing env var is placed
**	if set == -1 it's a new env_var
**  char *cmd: the env var. examples: "MY_VAR"(unassigned) or "MY_VAR=hey"
*/
void	mini_export_execve_edition(t_sh_data *sh, int set, char *cmd)
{
	char	**new_env;
	char	*var_value;

	new_env = dup_sh_env(sh->env, set);
	if (new_env == NULL)
		printf("mini_export_execve_edition(): malloc failure\n");
	if (set != -1)
	{
		var_value = ft_strchr(cmd, '=');
		if (var_value != NULL)
		{
			free(new_env[set]);
			new_env[set] = ft_strdup(cmd);
			if (new_env[set] == NULL)
				printf("mini_export_execve_edition(): malloc failure2\n");
		}
	}
	else
		add_shenv_var(sh, new_env, cmd);
	sh->env = new_env;
	if (sh->env == NULL)
		printf("mini_export_execve_edition(): something went wrong\n");
}
