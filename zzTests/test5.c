#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
"$noenv"SHLVL returns ""SHLVL, remove_quotes() should take care of the double quotes later
*/

// Node structure for linked list
/*typedef struct EnvNode {
    char *var_name;
    char *var_content;
    struct EnvNode *next;
} EnvNode;

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
            return current->var_content;
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
	//int ite;
	printf("expanded_var: var_name is: %s\n", env_pair[0]);
	printf("expanded_var: var_content is: %s\n", env_pair[1]);
	printf("expanded_var: head is: %s\n", (char *)head->var_name);
	printf("expanded_var: input is: %s\n", input);
	printf("expanded_var: j is: %d\n", *start);
	if (env_pair == NULL || *env_pair == NULL)
		return NULL;
	//ite = *start + 1;
	(*start)++;
	vname_len = strlen(env_pair[0]) + 1; // + 1 to include '$'
	if (vname_len == 1/* && strlen(input) == 1)
		return input;
	printf("expanded_var: vname_len is %d\n", vname_len);
	exp_len = strlen(env_pair[1]);
	printf("expanded_var: exp_len is %d\n", exp_len);
	new_len = strlen(input) - vname_len + exp_len;
	printf("expanded_var: new_len is %d\n", new_len);
	exp_str = (char *)malloc(new_len + 1);
	if (exp_str == NULL)
		return NULL;
	//copy the part before expanded_var
	strncpy(exp_str, input, (*start) -1);
	//copy the expanded_var
	strncpy(exp_str + (*start -1), env_pair[1], exp_len);
	//copy the part after expanded_var
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

	printf("get_var_content: start is %d\n", start);
	var_len = start;
	while (input[var_len] != '\0' && (ft_isalnum(input[var_len]) ==1|| input[var_len] =='_'))
		var_len++;
	printf("get_var_content: var_len is %d\n", var_len);
	printf("get_var_content: var_name_len is:%d\n", var_len - start +1);
	var_name = malloc (var_len - start + 1);
	if (var_name == NULL)
		return NULL;
	strncpy(var_name, &input[start], var_len - start); //ft_strlcpy
	var_name[var_len - start] = '\0';
	printf("get_var_content: var_name is %s\n", var_name);
	printf("get_var_content: var_name size is %ld\n", strlen(var_name));
	if (var_name[strlen(var_name)] == '\0') // to be removed
		printf("get_var_content: var_name[%ld] is: NIL!\n", strlen(var_name));
	result = (char **)malloc(sizeof(char*)*3);
    if (result == NULL)
    {
        free(var_name);
        return NULL;
    }
    result[0] = strdup(var_name);
	printf("result 0 is: %s\n", result[0]);
    var_content = find_env_pair(head, var_name) ;
    result[1] = var_content;
	printf("result 1 is: %s\n", result[1]);
    result[2] = NULL;
	return result;
}

char  **env_parse (int single_q, int double_q, char **input, EnvNode *env_list )
{
	char **env_pair;
	int i;
	int j;

	i = 0;
	while (input[i] != NULL)
	{
		j = 0;
		while (input[i][j] != '\0')
		{
			printf("j is: %d\n", j);
			if (env_quotes(input[i][j], &single_q, &double_q, &j) == 1)
			{
				printf("env_quotes returns 1\n");
				continue;
			}
			printf("env_quotes returns 0\n");
			if (input[i][j] == '$' && single_q == 0)
			{
				printf("j is: %d\n", j);
				env_pair = get_var_content(input[i], j +1, env_list);
				if (strcmp(env_pair[1], "") == 0)
					printf("find_env_pair returns: empty string!\n");
				else
					printf("find_env_pair returns: %s\n", env_pair[1]);
				printf("j is: %d\n", j);
				printf("i is: %d\n", i);
				input[i] = expanded_var(env_pair, env_list, input[i], &j);
				printf("env_parse: j is: %d\n", j);
				printf("env_parse: input is: %s\n", input[i]);
				if (input[i] == NULL)
					return NULL;
			}
	
			else
			{
				printf("j++!\n");
				j++;
			}

		}
		printf("i++\n");
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
    char *input[] = {"$\'-z\'", NULL};
    // Example linked list for environment variables
    EnvNode shlvl = {"SHLVL", "1", NULL};
    EnvNode path = {"PATH", "/usr/bin", NULL};
	EnvNode user = {"USER1234", "mikel", NULL};
    shlvl.next = &path;
	path.next =&user;
    env_parse(0, 0, input, &shlvl);
    print_expanded(input);

	//Free allocated memory [SEG-FAULTS!!]
    /*for (int i = 0; input[i] != NULL; i++) {
      free(input[i]);
   }

    return 0;
}*/


