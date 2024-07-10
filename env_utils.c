#include "minishell.h"

/*Need to manage memory allocated in ft_strdup!!
*/
t_env	*env_create_node(char *var_name, char *var_content)
{
	t_env	*new_node;

	new_node = malloc(sizeof(struct s_env));
	if (new_node == NULL)
		return (NULL);
	new_node->env_name = ft_strdup(var_name);
    if (var_content == NULL)
        new_node->env_value = NULL;
    else
	    new_node->env_value = ft_strdup(var_content);
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