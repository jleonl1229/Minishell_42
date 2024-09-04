#include "../minishell.h"

/*
** getenv(envvar_name) -->returns NULL if no env_var found or a pointer to the value
** chdir(absolute path to directory)--> returns 0 if successfully changed to directory, -1 otherwise
**	getcwd()--> returns char * (the absolute path of current wd) if success or NULL if failure
*/


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

int is_directory(char *fname) 
{
    DIR *dir;

	dir = opendir(fname);

    if (dir != NULL) 
	{
        closedir(dir);
        return 1;
    } 
	else
        return 0;
}


void cd_create_update(char *env_name, char *env_value, t_sh_data *sh, int flag)
{
	char **env_var;
	char *execve_var;
	int set;

	env_var = malloc(sizeof(char *) * 3);
	env_var[0] = ft_strdup(env_name);
	env_var[1] = ft_strdup(env_value);
	env_var[2] = NULL;
	if (ft_strncmp(env_name, "PWD", ft_strlen("PWD")) == 0
	&& ft_strlen(env_name) == ft_strlen("PWD"))
		execve_var = ft_strjoin("PWD=", env_value); 
	else 
		execve_var = ft_strjoin("OLDPWD=", env_value);
	if (flag == 1) //create env
	{
		add_env_var(env_var, sh->env_header);
		mini_export_execve_edition(sh, -1, execve_var);
	}
	else //update env
	{
		env_var_update(env_var, sh->env_header);
		set = is_var_set(sh->env_header, "PWD");
		mini_export_execve_edition(sh, set, execve_var);
	}
}


/*
**	by default (at least in my laptop's version) Bash inits Shell with PWD and without OLDPWD
**	if I unset PWD, unless I use "export" I shouldn't be creating a PWD env_var
**	the same goes for OLDPWD. need to check this in school computers!!! because if that's the
**	behavior I need to change the code
*/
int update_env_directories (t_sh_data *sh, char *old_dir)
{
	char cdir[MAX_PATH];

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
	return 0;
}


//CD WITHOUT ARGUMENTS ---- CHANGE TO HOME
int chdir_home(t_sh_data *sh, char *old_dir)
{
	int res;
	char *path;

	res = 0;
	path = custom_getenv(sh->env_header, "HOME");
	if (path == NULL) //no home env_var found
		return printf("cd: HOME not set\n");
	else if (path[0] == '\0') //unassigned env_var
		return 0; //doesn't error, doesn't do anything
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
