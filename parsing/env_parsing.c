#include "../minishell.h"



char	*expanded_var (char **env_pair, char *input, int *start)
{
	int exp_len;
	int new_len;
	char *exp_str;
	int vname_len;

	if (env_pair == NULL || *env_pair == NULL)
		return NULL;
	(*start)++;
	vname_len = strlen(env_pair[0]) + 1; // + 1 to include '$'
	if (vname_len == 1 && ft_strlen(input) != 1 && ft_strncmp(input, "$", ft_strlen("$")) == 0)
		return strdup(input +1);
	else if (vname_len ==1)
		return strdup(input);
	exp_len = strlen(env_pair[1]);
	new_len = strlen(input) - vname_len + exp_len;
	exp_str = (char *)malloc(new_len + 1);
	if (exp_str == NULL)
		return NULL;
	strncpy(exp_str, input, (*start) -1);
	strncpy(exp_str + (*start -1), env_pair[1], exp_len);
	strncpy(exp_str + (exp_len + *start -1), input + (*start-1) + vname_len, 
					strlen(input) - (*start -1) - vname_len + 1); // +1 for null char
	*start = *start - 1;
	return exp_str;
}

char **get_var_content(char *input, int start, t_env *head)
{
	int var_len;
	char *var_name;
	char *var_content;
	char **result;

	var_len = start;
	while (input[var_len] != '\0' && (ft_isalnum(input[var_len]) ==1|| input[var_len] =='_'))
		var_len++;
	var_name = malloc (var_len - start + 1);
	if (var_name == NULL)
		return NULL;
	strncpy(var_name, &input[start], var_len - start); //ft_strlcpy
	var_name[var_len - start] = '\0';
	result = (char **)malloc(sizeof(char*)*3);
    if (result == NULL)
    {
        free(var_name);
        return NULL;
    }
    result[0] = strdup(var_name); //unprotected
    var_content = find_env_pair(head, var_name) ;
    result[1] = var_content;
    result[2] = NULL;
	return result;
}

char *act_on_dollar(char *input, int *j, t_env *env_list)
{
    char *old_input;
    char **env_pair;
    int i;

    old_input = input;
    i = (*j) +1;
	env_pair = get_var_content(input, i, env_list);
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

char  **env_parse (int single_q, int double_q, char **input, t_env *env_list )
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
                input[i] = act_on_dollar(input[i], &j, env_list);
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
