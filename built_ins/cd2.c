/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleon-la <jleon-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:54:33 by jleon-la          #+#    #+#             */
/*   Updated: 2024/09/04 19:55:53 by jleon-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//CD WITHOUT ARGUMENTS ---- CHANGE TO HOME
int	chdir_home(t_sh_data *sh, char *old_dir)
{
	int		res;
	char	*path;

	res = 0;
	path = custom_getenv(sh->env_header, "HOME");
	if (path == NULL)
		return (printf("cd: HOME not set\n"));
	else if (path[0] == '\0')
		return (0);
	else
	{
		if (chdir(path) == 0)
			res = update_env_directories(sh, old_dir);
		else
		{
			perror("cd");
			return (1);
		}
	}
	return (res);
}

int	chdir_oldpwd(t_sh_data *sh, char *old_dir)
{
	char	*path;
	int		res;

	path = custom_getenv(sh->env_header, "OLDPWD");
	res = 0;
	if (path == NULL)
		return (printf("cd: OLDPWD not set\n"));
	else if (path[0] == '\0')
		return (0);
	if (chdir(path) == 0)
	{
		printf("%s\n", path);
		res = update_env_directories(sh, old_dir);
	}
	else
	{
		perror("cd");
		return (1);
	}
	return (res);
}

int	chdir_basecase(t_parsed_data *header, t_sh_data *sh, char *old_dir)
{
	char	**cmd;
	int		res;

	cmd = header->cmd;
	if (access(cmd[1], F_OK) == 0)
	{
		if (is_directory(cmd[1]))
		{
			if (chdir(cmd[1]) == 0)
				res = update_env_directories(sh, old_dir);
			else
			{
				perror("cd");
				res = 1;
			}
		}
		else
			res = printf("cd: %s: Not a directory\n", cmd[1]);
	}
	else
		res = printf("cd: %s: No such file or directory\n", cmd[1]);
	return (res);
}

/*
** cd's functionality includes:
**		1. "cd" or "cd --" will change pwd to HOME
**		2. "cd -" will change to the previous pwd and print its name.
**		equivalent to doing: "cd "$OLDPWD" && pwd"
haven't implemented functionality for the tilde char 
**		(~, shorthand for the home dir path)
*/
int	do_cd(t_parsed_data *header, t_sh_data *sh, char *pwd)
{
	int		res;
	char	**cmd;

	cmd = header->cmd;
	if (cmd[1] == NULL || (ft_strncmp(cmd[1], "--", ft_strlen("--")) == 0
			&& ft_strlen("--") == ft_strlen(cmd[1])))
		res = chdir_home(sh, pwd);
	else if (cmd[1] != NULL && cmd[2] != NULL)
		res = printf("cd: too many arguments\n");
	else if (ft_strncmp(cmd[1], "-", ft_strlen("-")) == 0
		&& ft_strlen("-") == ft_strlen(cmd[1]))
		res = chdir_oldpwd(sh, pwd);
	else
		res = chdir_basecase(header, sh, pwd);
	if (res != 0)
		res = 1;
	return (res);
}

/*
**	pwd is the old_dir, to be passed as parameter between aux functions
*/
int	mini_cd(t_parsed_data *header, t_sh_data *sh)
{
	char	pwd[MAX_PATH];

	if (getcwd(pwd, MAX_PATH) == NULL)
		return (1);
	if (is_simple_cmd(sh) == 1)
		return (do_cd(header, sh, pwd));
	return (1);
}
