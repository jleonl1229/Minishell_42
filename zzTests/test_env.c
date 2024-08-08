#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
"$noenv"SHLVL returns ""SHLVL, remove_quotes() should take care of the double quotes later
*/

// Node structure for linked list
typedef struct EnvNode {
    char *var_name;
    char *var_content;
    struct EnvNode *next;
} EnvNode;

char	**free_matrix(char **pointer)
{
	int	i;

	i = 0;
    if (pointer == NULL)
        return NULL;
    while (pointer[i] != NULL)
	{
		free(pointer[i]);
        pointer[i] = NULL;
		++i;
	}
	free(pointer);
    pointer = NULL;
	return (NULL);
}

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		return (1);
	}
	return (0);
}

int env_quotes(char c, int *single_q, int *double_q, int *j)
{
	if (c == '\"' && *single_q == 0) 
	{
        *double_q = !*double_q;
		(*j)++;
		return 1;
	}
    else if (c == '\'' && *double_q == 0) 
	{
        *single_q = !*single_q;
		(*j)++;
		return 1;
    }
	
	return 0;
}

char *find_env_pair(EnvNode *head, char *var_name) 
{
    EnvNode *current = head;
    while (current != NULL) 
	{
        if (strncmp(current->var_name, var_name, strlen(var_name)) == 0 
		&& strncmp(current->var_name, var_name, strlen(current->var_name)) == 0) //ft_strncmp
        {
            free(var_name);
			if (current->var_content != NULL)
				return strdup(current->var_content);
			else
				return strdup("");
        }
		current = current->next;
    }
    free(var_name);
    return strdup("");
}


char	*expanded_var (char **env_pair, EnvNode *head, char *input, int *start)
{
	int exp_len;
	int new_len;
	char *exp_str;
	int vname_len;

	//printf("expanded_var: var_name is: %s\n", env_pair[0]);
	//printf("expanded_var: var_content is: %s\n", env_pair[1]);
	//printf("expanded_var: head is: %s\n", (char *)head->var_name);
	//printf("expanded_var: input is: %s\n", input);
	//printf("expanded_var: j is: %d\n", *start);
	if (env_pair == NULL || *env_pair == NULL)
		return NULL;
	(*start)++;
	vname_len = strlen(env_pair[0]) + 1; // + 1 to include '$'
	if (vname_len == 1)
		return strdup(input);
	exp_len = strlen(env_pair[1]);
	//printf("expanded_var: exp_len is %d\n", exp_len);
	new_len = strlen(input) - vname_len + exp_len;
	//printf("expanded_var: new_len is %d\n", new_len);
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


char **get_var_content(char *input, int start, EnvNode *head)
{
	int var_len;
	char *var_name;
	char *var_content;
	char **result;

	//printf("get_var_content: input is: %s\n", input);
	//printf("get_var_content: start is : %d", start);
	var_len = start;
	while (input[var_len] != '\0' && (ft_isalnum(input[var_len]) ==1|| input[var_len] =='_'))
		var_len++;
	//printf("get_var_content: var_len is %d\n", var_len);
	//printf("get_var_content: var_name_len is:%d\n", var_len - start +1);
	var_name = malloc (var_len - start + 1);
	if (var_name == NULL)
		return NULL;
	strncpy(var_name, &input[start], var_len - start); //ft_strlcpy
	var_name[var_len - start] = '\0';
	//printf("get_var_content: var_name is %s\n", var_name);
	//printf("get_var_content: var_name size is %ld\n", strlen(var_name));
	if (var_name[strlen(var_name)] == '\0') // to be removed
	//printf("get_var_content: var_name[%ld] is: NIL!\n", strlen(var_name));
	result = (char **)malloc(sizeof(char*)*3);
    if (result == NULL)
    {
        free(var_name);
        return NULL;
    }
    result[0] = strdup(var_name);
	//printf("result 0 is: %s\n", result[0]);
    var_content = find_env_pair(head, var_name) ;
    result[1] = var_content;
	//printf("result 1 is: %s\n", result[1]);
    result[2] = NULL;
	return result;
}


char *act_on_dollar(char *input, int *j, EnvNode *env_list)
{
    char *old_input;
    char **env_pair;
    int i;

	//printf("act_on_dollar: input is: %s\n", input);
	//printf("act_on_dollar: j is: %d\n", *j);
    old_input = input;
	//printf("act_on_dollar: old_input is: %s\n", old_input);
    i = (*j) +1;
	env_pair = get_var_content(input, i, env_list);
	//if (strcmp(env_pair[1], "") == 0)
		//printf("find_env_pair returns: empty string!\n");
	//else
		//printf("find_env_pair returns: %s\n", env_pair[1]);
	//printf("j is: %d\n", *j);
	//printf("i is: %d\n", i);
	input = expanded_var(env_pair, env_list, input, j);
	//printf("act_on_dollar: j is: %d\n", *j);
	//printf("act_on_dollar: input is: %s\n", input);
	if (input == NULL)
	{
        free_matrix(env_pair);
        return NULL;
	}
	free(old_input);
    free_matrix(env_pair);
    return input;
}

char  **env_parse (int single_q, int double_q, char **input, EnvNode *env_list )
{
	int i;
	int j;

	i = 0;
	while (input[i] != NULL)
	{
		j = 0;
		while (input[i][j] != '\0')
		{
			//printf("j is: %d\n", j);
			if (env_quotes(input[i][j], &single_q, &double_q, &j) == 1)
			{
				//printf("env_quotes returns 1\n");
				continue;
			}
			//printf("env_quotes returns 0\n");
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


void print_expanded(char **input) {
    for (int i = 0; input[i] != NULL; i++) {
        printf("%s ", input[i]);
    }
    printf("\n");
}

int main() {
    char *input[] = {strdup("$CASIO"), NULL};
    // Example linked list for environment variables
	EnvNode shlvl = {strdup("SHLVL"), strdup(""), NULL};
	EnvNode path = {strdup("PATH"), strdup("/usr/bin"), NULL};
	//EnvNode user = {strdup("USER1234"), strdup("mikel"), NULL};
    shlvl.next = &path;
	//path.next =&user;
    env_parse(0, 0, input, &shlvl);
    print_expanded(input);
	free(shlvl.var_name);
	free(shlvl.var_content);
	free(path.var_name);
	free(path.var_content);
	//Free allocated memory [SEG-FAULTS!!]
    for (int i = 0; input[i] != NULL; i++) {
      free(input[i]);
   }

    return 0;
}






/*char  **env_parse (int single_q, int double_q, char **input, EnvNode *env_list )
{
	char **env_pair;
	int i;
	int j;
	char *old_input;

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
				old_input = input[i];
				env_pair = get_var_content(input[i], j +1, env_list);
				//printf("input i points to: %p\n", input[i]);
				input[i] = expanded_var(env_pair, env_list, input[i], &j);
				//printf("old_input is: %s\n", old_input);
				//printf("input i points to: %p\n", input[i]);
				////printf("input[%d] is: %s\n", i, input[i]);
				if (input[i] == NULL)
				{
					free_matrix(env_pair);
					return NULL;
				}
				free(old_input);
				free_matrix(env_pair);
			}
			else
				j++;
		}
		i++;
	}
	return input;
}*/