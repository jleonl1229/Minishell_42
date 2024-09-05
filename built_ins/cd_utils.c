#include "../minishell.h"

//checks if inputed str is a directory or not
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

void cd_create(char **env_var, t_sh_data *sh, int set, char *execve_var)
{
    add_env_var(env_var, sh->env_header);
    mini_export_execve_edition(sh, set, execve_var);
}

void cd_update(char **env_var, t_sh_data *sh, int set, char *execve_var)
{
    env_var_update(env_var, sh->env_header);
    set = is_var_set(sh->env_header, "PWD");
    mini_export_execve_edition(sh, set, execve_var);
}

void cd_create_update(char *env_name, char *env_value, t_sh_data *sh, int flag)
{
	char **env_var;
	char *execve_var;

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
        cd_create(env_var, sh, -1, execve_var);
	else
        cd_update(env_var, sh, -2, execve_var);
    free(execve_var);
    free_matrix(env_var);
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
