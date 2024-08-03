#include "../minishell.h"

/*
** auxiliary to env_parse()
*/
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



/*
**	auxiliary to env_parse()
*/
char *find_env_pair(t_env *head, char *var_name) 
{
    t_env *current = head;
    while (current != NULL) 
	{
        if (strncmp(current->env_name, var_name, strlen(var_name)) == 0 
		&& strncmp(current->env_name, var_name, strlen(current->env_name)) == 0) //ft_strncmp
        {
            free(var_name);
            return strdup(current->env_value);
        }
		current = current->next;
    }
    free(var_name);
    return strdup("");
}

t_env	*env_create_node(char *var_name, char *var_content)
{
	t_env	*new_node;

	new_node = malloc(sizeof(struct s_env));
	if (new_node == NULL)
		return (NULL);
	new_node->env_name = ft_strdup(var_name);
	if (new_node->env_name == NULL)
	{
		free(new_node);
		return NULL;
	}
    if (var_content == NULL)
        new_node->env_value = NULL;
    else
	{
		new_node->env_value = ft_strdup(var_content);
		if (new_node->env_value == NULL)
		{
			free(new_node->env_name);
			free(new_node);
			return NULL;
		}
	}
	new_node->next = NULL;
	return (new_node);
}

//adds node to the bottom of the list
void	env_add_node(t_env **header, t_env *new_node)
{
	t_env	*temp;

	if (header == NULL || new_node == NULL)
		return ;
	if (*header == NULL) //first node in the list
	{
		*header = new_node;
		return ;
	}
	temp = *header;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
}