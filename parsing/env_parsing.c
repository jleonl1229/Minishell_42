#include "../minishell.h"

/*
** first I used strncpy, then had to change to ft_strlcpy, but as both functions aren't exactly
** the same, I'm keeping it for the moment.
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
	//strncpy(exp_str, input, (*start) -1);
	ft_strlcpy(exp_str, input, *start);
	//strncpy(exp_str + (*start -1), env_pair[1], exp_len);
	ft_strlcpy(exp_str + (*start -1), env_pair[1], exp_len +1);
	//strncpy(exp_str + (exp_len + *start -1), input + (*start-1) + vname_len, 
					//strlen(input) - (*start -1) - vname_len + 1); // +1 for null char
	ft_strlcpy(exp_str + (exp_len + *start -1), input + (*start -1) + vname_len,
					ft_strlen(input) - (*start -1) - vname_len +1);
	*start = *start - 1;
	return exp_str;
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
	//printf("start is: %d\n", start);
	while (input[var_len] != '\0' && (ft_isalnum(input[var_len]) ==1|| input[var_len] =='_' 
	|| (start - var_len == 0 && input[var_len] == '?' )))
		var_len++;
	//printf("var_len is: %d\n", var_len);
	var_name = malloc (var_len - start + 1);
	if (var_name == NULL)
		return NULL;
	ft_strlcpy(var_name, &input[start], var_len - start + 1);
	result = (char **)malloc(sizeof(char*)*3);
    if (result == NULL)
    {
        free(var_name);
        return NULL;
    }
    result[0] = ft_strdup(var_name);
	if (result[0] == NULL)
	{
		free(var_name);
		return free_matrix(result);
	}
	//printf("var_name is: %s\n", var_name);
	if (ft_strncmp(var_name, "?", ft_strlen(var_name)) == 0 && ft_strlen(var_name) == ft_strlen("?"))
		var_content = ft_strdup(sh->last_exit_status/*"_LAST_EXIT_STATUS_"*/);
	else
    	var_content = find_env_pair(sh->env_header, var_name); 
	if (var_content == NULL)
		return free_matrix(result);
    result[1] = var_content;
    result[2] = NULL;
	return result;
}

char *act_on_dollar(char *input, int *j, t_sh_data *sh)
{
    char *old_input;
    char **env_pair;
    int i;
	//char *hardcode[] = {"$?", "_LAST_EXIT_STATUS_", NULL};

	//printf("act_on_dollar(): input is: %s\n", input);
    old_input = input;
    i = (*j) +1;
	env_pair = get_var_content(input, i, sh);
	int k = 0;
	while(env_pair[k] != NULL)
	{
		//printf("env_pair[%d] is : %s\n", k, env_pair[k]);
		k++;
	}
	//printf("input is: %s\n", input);
	if (env_pair == NULL)
		return NULL;		
	input = expanded_var(env_pair, input, j);
	//printf("input after expanded_var is: %s\n", input);
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
**	if command is "<infile cat | wc -l >out"
**	char **input is: ["<", "infile", "cat"]
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

