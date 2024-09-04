/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleon-la <jleon-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:25:29 by jleon-la          #+#    #+#             */
/*   Updated: 2024/09/04 19:55:50 by jleon-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// getenv(envvar_name) -->returns NULL if no env_var 
// found or a pointer to the value

// chdir(absolute path to directory)--> 
// returns 0 if successfully changed to directory, -1 otherwise

// getcwd()--> returns char * (the absolute path of current wd) 
// if success or NULL if failure

char	*custom_getenv(t_env *head, const char *name)
{
	t_env	*current;

	current = head;
	while (current != NULL)
	{
		if (ft_strncmp(current->env_name, name, ft_strlen(name)) == 0
			&& ft_strlen(current->env_name) == ft_strlen(name))
			return (current->env_value);
		current = current->next;
	}
	return (NULL);
}

int	is_directory(char *fname)
{
	DIR	*dir;

	dir = opendir(fname);
	if (dir != NULL)
	{
		closedir(dir);
		return (1);
	}
	else
		return (0);
}

void	cd_create_update(char *env_name, char *env_value,
		t_sh_data *sh, int flag)
{
	char	**env_var;
	char	*execve_var;
	int		set;

	env_var = malloc(sizeof(char *) * 3);
	env_var[0] = ft_strdup(env_name);
	env_var[1] = ft_strdup(env_value);
	env_var[2] = NULL;
	if (ft_strncmp(env_name, "PWD", ft_strlen("PWD")) == 0
		&& ft_strlen(env_name) == ft_strlen("PWD"))
		execve_var = ft_strjoin("PWD=", env_value);
	else
		execve_var = ft_strjoin("OLDPWD=", env_value);
	if (flag == 1)
	{
		add_env_var(env_var, sh->env_header);
		mini_export_execve_edition(sh, -1, execve_var);
	}
	else
	{
		env_var_update(env_var, sh->env_header);
		set = is_var_set(sh->env_header, "PWD");
		mini_export_execve_edition(sh, set, execve_var);
	}
}
// by default (at least in my laptop's version) 
// Bash inits Shell with PWD and without OLDPWD

// if I unset PWD, unless I use "export" I shouldn't 
// be creating a PWD env_var

// the same goes for OLDPWD. need to check this in
//  school computers!!! because if that's the
// behavior I need to change the code
int	update_env_directories(t_sh_data *sh, char *old_dir)
{
	char	cdir[MAX_PATH];

	if (getcwd(cdir, MAX_PATH) == NULL)
		return (1);
	if (custom_getenv(sh->env_header, "PWD") == NULL)
		cd_create_update("PWD", cdir, sh, 1);
	else
		cd_create_update("PWD", cdir, sh, 0);
	if (custom_getenv(sh->env_header, "OLDPWD") == NULL)
		cd_create_update("OLDPWD", old_dir, sh, 1);
	else
		cd_create_update("OLDPWD", old_dir, sh, 0);
	return (0);
}
