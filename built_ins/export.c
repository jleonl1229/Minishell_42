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
void    add_env_var(char **env_var, t_env *env)
{
    t_env *new_node;

    new_node = env_create_node(env_var[0], env_var[1]);
    env_add_node(&env, new_node);

}

/*
**  updates var_value in t_env*
*/
void    env_var_update(char **env_var, t_env *env)
{
	while (env != NULL)
	{
        if (ft_strncmp(env->env_name, env_var[0], ft_strlen(env_var[0])) == 0
        && ft_strlen(env->env_name) == ft_strlen(env_var[0]))
        {
            free(env->env_value);
            env->env_value = strdup(env_var[1]);
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
void no_arg_export(t_env *env)
{
    t_env *sorted;
    t_env *temp;

    sorted = dup_env(env);
    if (sorted == NULL)
        printf("export(): sorted - env deleted?\n");
    sort_lst(&sorted);
    temp = sorted;
    while (temp != NULL)
    {
        printf("declare -x "); //both for assigned and unassigned
        if (temp->env_value == NULL) //unassigned env_vars
            printf("%s\n", temp->env_name);
        else //assigned env_vars
            printf("%s=\"%s\"\n", temp->env_name, temp->env_value);
        temp = temp->next;
    }
    free_env_list(sorted);
}

/*
**  export can be used without args (coded no_arg_export()) or with args
**  if "export" with args -> each arg can be a new env_var (that needs to be added)
**  params:
**  The program has 2 data structures to represent the env_vars: a linked list (easily retrieve PATH)
**  and a char ** (needed format for execve). This means that both will need to be updated with the
**  new env_vars. 
**      1. linked list or char **env as source of up to date env_vars
**      2. char ** as a source of up to date env_vars
**      1. header->cmd to get the cmd + its args
*/

int mini_export (t_parsed_data *header, t_sh_data *sh)
{
    char *arg;
    char **cmd;
    char **env_var;
    int set;

    cmd = header->cmd;
    if (cmd[1] == NULL || ft_strlen(cmd[1]) == 0)
    {
        no_arg_export(sh->env_header);
        return 0;
    }

    while (*(++cmd) != NULL)
    {
        arg = *cmd;
        printf("arg is: %s\n", arg);
        if (is_valid_arg_export(arg) == 0) //is invalid
            return (1); //failure
        if (is_simple_cmd(sh) == 1)
        {
            env_var = get_var_data(arg); //unprotected
            printf("env_var[0] is: %s\n", env_var[0]);
            printf("env_var[1] is: %s\n", env_var[1]);
            if (env_var[1] != NULL)
                printf("env_var[2] is: %s\n", env_var[2]);
            set = is_var_set(sh->env_header, env_var[0]);
            printf("set is: %d\n", set);
            mini_export_execve_edition(sh, set, arg);
            if (set != -1) //existing env_var
            {
                if (env_var[1] != NULL) //true if assigned var
                    env_var_update(env_var, sh->env_header);
            }
            else
                add_env_var(env_var, sh->env_header);
            free_matrix(env_var);
        }
    }
    return 0;
}


