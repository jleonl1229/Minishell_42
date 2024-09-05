/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:44:17 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/09/04 19:52:19 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**  makes a copy of env and stores it in a linked list data structure.
**  t_sh_data gets a pointer to the head
*/
t_env	*parse_env(char **envp, t_env *header, t_sh_data **sh)
{
	char	*var_name;
	char	*var_content;
	char	**a_env;
	char	**org;
	t_env	*new_node;

	while (*envp != NULL)
	{
		a_env = env_split(*envp, '=');
		org = a_env;
		if (a_env == NULL || *a_env == NULL)
			pre_parse_cleanup(sh, header, org);
		var_name = *a_env;
		var_content = *(++a_env);
		new_node = env_create_node(var_name, var_content);
		if (new_node == NULL)
			pre_parse_cleanup(sh, header, org);
		env_add_node(&header, new_node);
		free_matrix(org);
		envp++;
	}
	return (header);
}

/*
** removing OLDPWD from env_vars, same as a fresh Bash session
**
*/
char	**populate_env(char **envp)
{
	int		i;
	char	**env;
	int		rem;

	i = 0;
	rem = -1;
	while (envp[i] != NULL)
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (env == NULL)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "OLDPWD=", 7) != NULL)
			rem = i;
		env[i] = ft_strdup(envp[i]);
		if (env[i] == NULL)
			return (NULL);
		i++;
	}
	env[i] = NULL;
	if (rem != -1)
		unset_remove_shenv(env, rem);
	return (env);
}

/*
**  isatty checks if minishell input coming from terminal
**  the OLDPWD env_var is removed, just like in Bash 
**	when a new session is started
*/
void	shell_init(t_sh_data **sh, char **envp)
{
	t_env	*header;

	header = NULL;
	if (!isatty(STDIN_FILENO))
	{
		free(*sh);
		perror("terminal is not STDIN");
		exit(EXIT_SUCCESS);
	}
	(*sh)->env_header = NULL;
	(*sh)->prev_line = NULL;
	(*sh)->parsed_header = NULL;
	(*sh)->new_line = NULL;
	(*sh)->env_header = parse_env(envp, header, sh);
	unset_remove_tenv("OLDPWD", &((*sh)->env_header), 1);
	(*sh)->env = populate_env(envp);
	if ((*sh)->env == NULL)
		printf("free&exit function goes here\n");
	(*sh)->last_exit_status = ft_strdup("0");
	if ((*sh)->last_exit_status == NULL)
		printf("free&exit function goes here\n");
}
