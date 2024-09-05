/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:55:39 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/09/05 17:05:46 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**  Unassigned environment vars have NULL as their t_env.env_value 
**  to differentiate between assigned empty string environment vars ("")
**
**  "export $SHLVL" expands to "export 1" (creating an unassigned env_var)
**  "export $user" executes as "export", because $user expands to an empty string
**  "export VAR1=one VAR2=two -->creates 2 vars
**  "export VAR1="one" VAR2="two"" -->creates 2 vars, values get quotes removed
**  "export HEY = hola" -->returns error because "=" not accepted as var_name
**  "export HEY hola" --> creates 2 unassigned vars
*/

/*
**  adds the new env_var to the t_env linked list
*/
void	add_env_var(char **env_var, t_env *env)
{
	t_env	*new_node;

	new_node = env_create_node(env_var[0], env_var[1]);
	env_add_node(&env, new_node);
}

/*
**  updates var_value in t_env*
*/
void	env_var_update(char **env_var, t_env *env)
{
	while (env != NULL)
	{
		if (ft_strncmp(env->env_name, env_var[0], ft_strlen(env_var[0])) == 0
			&& ft_strlen(env->env_name) == ft_strlen(env_var[0]))
		{
			free(env->env_value);
			env->env_value = ft_strdup(env_var[1]);
		}
		env = env->next;
	}
}

/*
**  to be used when export is casted without args
**  lists every env_var (+ unassigned ones) with the following formatting:
**      1. add "declare -x" before the env_var_name 
**      2. add double quotes to env_var_value
**      3. lists unassigned env_vars
**      4. sorted in alphabetical order
*/
void	no_arg_export(t_env *env)
{
	t_env	*sorted;
	t_env	*temp;

	sorted = dup_env(env);
	if (sorted == NULL)
		printf("export(): sorted - env deleted?\n");
	sort_lst(&sorted);
	temp = sorted;
	while (temp != NULL)
	{
		printf("declare -x ");
		if (temp->env_value == NULL)
			printf("%s\n", temp->env_name);
		else
			printf("%s=\"%s\"\n", temp->env_name, temp->env_value);
		temp = temp->next;
	}
	free_env_list(sorted);
}

/*
**  set == -1 means its a new env_var
**  env_var[1] != NULL will be true if it's an assigned var
*/
void	simple_export(char **env_var, int set, char *arg, t_sh_data *sh)
{
	env_var = get_var_data(arg);
	set = is_var_set(sh->env_header, env_var[0]);
	mini_export_execve_edition(sh, set, arg);
	if (set != -1)
	{
		if (env_var[1] != NULL)
			env_var_update(env_var, sh->env_header);
	}
	else
		add_env_var(env_var, sh->env_header);
	free_matrix(env_var);
}

/*
**  export can be used without args (coded no_arg_export()) or with args
**  if "export" with args -> each arg can be a new env_var (must be added)
**  params:
**  The program has 2 data structures to represent the env_vars: 
**	a linked list (easily retrieve PATH) and a char ** (needed for execve).
**	This means that both will need to be updated with the
**  new env_vars. 
**      1. linked list or char **env as source of up to date env_vars
**      2. char ** as a source of up to date env_vars
**      1. header->cmd to get the cmd + its args
*/
int	mini_export(t_parsed_data *header, t_sh_data *sh)
{
	char	*arg;
	char	**cmd;
	char	**env_var;
	int		set;

	env_var = NULL;
	cmd = header->cmd;
	set = -2;
	if (cmd[1] == NULL || ft_strlen(cmd[1]) == 0)
	{
		no_arg_export(sh->env_header);
		return (0);
	}
	while (*(++cmd) != NULL)
	{
		arg = *cmd;
		if (is_valid_arg_export(arg) == 0)
			return (1);
		if (is_simple_cmd(sh) == 1)
			simple_export(env_var, set, arg, sh);
	}
	return (0);
}
