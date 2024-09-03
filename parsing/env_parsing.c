#include "../minishell.h"

/*
**	returns the expanded str
*/
char	*expanded_var (char **env_pair, char *input, int *start)
{
	int exp_len;
	int new_len;
	char *exp_str;
	int vname_len;

	if (env_pair == NULL || *env_pair == NULL)
		return NULL;
	(*start)++;
	vname_len = ft_strlen(env_pair[0]) + 1; // + 1 to include '$'
	if (vname_len == 1 && ft_strlen(input) != 1 && ft_strncmp(input, "$", ft_strlen("$")) == 0)
		return ft_strdup(input +1);
	else if (vname_len ==1)
		return ft_strdup(input);
	exp_len = ft_strlen(env_pair[1]);
	new_len = ft_strlen(input) - vname_len + exp_len;
	exp_str = (char *)malloc(new_len + 1);
	if (exp_str == NULL)
		return NULL;
	ft_strlcpy(exp_str, input, *start);
	ft_strlcpy(exp_str + (*start -1), env_pair[1], exp_len +1);
	ft_strlcpy(exp_str + (exp_len + *start -1), input + (*start -1) + vname_len,
					ft_strlen(input) - (*start -1) - vname_len +1);
	*start = *start - 1;
	return exp_str;
}

/*
**	auxiliary to get_var_content, allocates for the char ** that will contain the data on
**	the env_var_name and value. Also fills the name of the env_var in var_name
*/
char **alloc_get_var_content(char *input, int var_len, int start, char **var_name)
{
	char **result;

	while (input[var_len] != '\0' && (ft_isalnum(input[var_len]) ==1|| input[var_len] =='_' 
	|| (start - var_len == 0 && input[var_len] == '?' )))
		var_len++;
	*var_name = malloc (var_len - start + 1);
	if (*var_name == NULL)
		return NULL;
	ft_strlcpy(*var_name, &input[start], var_len - start + 1);
	result = (char **)malloc(sizeof(char*)*3);
    if (result == NULL)
    {
        free(*var_name);
        return NULL;
    }
	return result;
}
/*
**	var_name is freed on find_env_pair for function max lines purposes
*/
char **get_var_content(char *input, int start, t_sh_data *sh)
{
	int var_len;
	char *var_name;
	char *var_content;
	char **result;

	var_len = start;
	var_name = NULL;
	result = alloc_get_var_content(input, var_len, start, &var_name);
	if (result == NULL)
		return NULL;
    result[0] = ft_strdup(var_name);
	if (result[0] == NULL)
	{
		free(var_name);
		return free_matrix(result);
	}
	if (ft_strncmp(var_name, "?", ft_strlen(var_name)) == 0 && ft_strlen(var_name) == ft_strlen("?"))
		var_content = ft_strdup(sh->last_exit_status);
	else
    	var_content = find_env_pair(sh->env_header, var_name); 
	if (var_content == NULL)
		return free_matrix(result);
    result[1] = var_content;
    result[2] = NULL;
	return result;
}

/*
**	if input is "$USER", it returns "mikel" 
**	calls get_var_content()-> fills env_var data
**	calls expanded_var()-> rewrites input with expanded data
*/
char *act_on_dollar(char *input, int *j, t_sh_data *sh)
{
    char *old_input;
    char **env_pair;
    int i;

    old_input = input;
    i = (*j) +1;
	env_pair = get_var_content(input, i, sh);
	if (env_pair == NULL)
		return NULL;		
	input = expanded_var(env_pair, input, j);
	if (input == NULL)
	{
        free_matrix(env_pair);
        return NULL;
	}
	free(old_input);
    free_matrix(env_pair);
    return input;
}

/*
**	traverses every char in every char *element of char ** looking for "$"
**	if command is "<infile cat | wc -l >out", char **input is: ["<", "infile", "cat"]
**	
*/
char  **env_parse (int single_q, int double_q, char **input, t_sh_data *sh)
{
	int i;
	int j;

	i = 0;
	while (input[i] != NULL)
	{
		j = 0;
		while (input[i][j] != '\0')
		{
			if (env_quotes(input[i][j], &single_q, &double_q, &j) == 1)
				continue;
			if (input[i][j] == '$' && single_q == 0)
            {
                input[i] = act_on_dollar(input[i], &j, sh);
                if (input[i] == NULL)
                    return NULL;
            }
			else
				j++;
		}
		i++;
	}
	return input;
}

