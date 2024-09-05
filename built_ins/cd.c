#include "../minishell.h"

/*
**	works both for "cd" and "cd --"
**	checks for manipulation of the HOME env_var:
**		1. if it has been deleted it prints a message
**		2.	if it's an unassigned var it doesn't do anything
*/
int chdir_home(t_sh_data *sh, char *old_dir)
{
	int res;
	char *path;

	res = 0;
	path = custom_getenv(sh->env_header, "HOME");
	if (path == NULL)
		return printf("cd: HOME not set\n");
	else if (path[0] == '\0')
		return 0;
	else
	{
		if (chdir(path) == 0)
			res = update_env_directories(sh, old_dir);
		else
		{
			perror("cd");
			return 1;
		}
	}
	return res;
}

/*
**	triggered when input is "cd -"
**	if it's the firs time using "cd" it would print an error
**	else, it will print the preivous directory and move there
*/
int chdir_oldpwd(t_sh_data *sh, char *old_dir)
{
    char *path;
	int res;

    path = custom_getenv(sh->env_header, "OLDPWD");
	res = 0;
    if (path == NULL)
        return printf("cd: OLDPWD not set\n");
	else if (path[0] == '\0')
		return 0;
    if (chdir(path) == 0)
    {
		printf("%s\n", path);
		res = update_env_directories(sh, old_dir);
    }
    else
    {
        perror("cd");
        return 1;
    }
    return res;
}

/*
**	if cd has 1 argument and its not one of aboves features
**	checks if the cd args exists and if its a directory, prints errors if not
*/
int chdir_basecase(t_parsed_data *header, t_sh_data *sh, char *old_dir)
{
	char **cmd;
	int res;

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
	return res;
}


/*
** cd's functionality includes:
**		1. "cd" or "cd --" will change pwd to HOME
**		2. "cd -" will change to the previous pwd and print its name.
**		equivalent to doing: "cd "$OLDPWD" && pwd"
**	haven't implemented functionality for the tilde char (~, shorthand for the home dir path)
*/
int do_cd(t_parsed_data *header, t_sh_data *sh, char *pwd)
{
	int res;
	char **cmd;

	cmd = header->cmd;
	if (cmd[1] == NULL || (ft_strncmp(cmd[1], "--", ft_strlen("--")) == 0 
	&& ft_strlen("--") == ft_strlen(cmd[1])))
		res = chdir_home(sh, pwd);
	else if (cmd[1] !=NULL && cmd[2] !=NULL)
		res = printf("cd: too many arguments\n");
	else if (ft_strncmp(cmd[1], "-", ft_strlen("-")) == 0 && ft_strlen("-") == ft_strlen(cmd[1]))
		res = chdir_oldpwd(sh, pwd);
	else
		res = chdir_basecase(header, sh, pwd);
	if (res !=0)
		res = 1;
	return res;
}

/*
**	pwd is the old_dir, to be passed as parameter between aux functions
** getenv(envvar_name) -->returns NULL if no env_var found or a pointer to the value
** chdir(absolute path to directory)--> returns 0 if successfully changed to directory, -1 otherwise
**	getcwd()--> returns char * (the absolute path of current wd) if success or NULL if failure
*/
int mini_cd(t_parsed_data *header, t_sh_data *sh)
{
	char pwd[MAX_PATH];

	if (getcwd(pwd, MAX_PATH) == NULL)
		return 1;
	if (is_simple_cmd(sh) == 1)
		return (do_cd(header, sh, pwd));
	return 1;
}
