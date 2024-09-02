#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct s_env {
    char *env_name;
    char *env_value;
    struct s_env *next;
} t_env;

void swap_nodes(t_env *a, t_env *b) 
{
    char *temp_name;
    char *temp_value;
    
    temp_name = a->env_name;
    temp_value = a->env_value;
    
    a->env_name = b->env_name;
    a->env_value = b->env_value;
    
    b->env_name = temp_name;
    b->env_value = temp_value;

}

/*
**
*/

void sort_lst(t_env **env)
{
    int swapped; 
    t_env *current;

    swapped = 1;
    if (*env == NULL)
        return; 
    while (swapped == 1)
    {
        swapped = 0;
        current = *env;
        while (current != NULL && current->next != NULL) 
        {
            if (strncmp(current->env_name, current->next->env_name, strlen(current->env_name) + 1) > 0) 
            {
                swap_nodes(current, current->next);
                swapped = 1;
            }
            current = current->next;
        }
    }
}

// Helper functions for creating nodes and printing the list
t_env *create_node(char *env_name, char *env_value) {
    t_env *new_node = (t_env *)malloc(sizeof(t_env));
    new_node->env_name = strdup(env_name);
	if (env_value == NULL)
		new_node->env_value = NULL;
	else
		new_node->env_value = strdup(env_value);
    new_node->next = NULL;
    return new_node;
}

void print_list(t_env *env) {
    while (env != NULL) {
        printf("%s=%s\n", env->env_name, env->env_value);
        env = env->next;
    }
}


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

t_env	*env_create_node(char *var_name, char *var_content)
{
	t_env	*new_node;
	//printf("ft_strlen(var_content) is: %ld\n", strlen(var_content));

	new_node = malloc(sizeof(struct s_env));
	if (new_node == NULL)
		return (NULL);
	new_node->env_name = strdup(var_name);
	if (new_node->env_name == NULL)
	{
		free(new_node);
		return NULL;
	}
    if (var_content == NULL) //unassigned var
        new_node->env_value = NULL;
	else if (strlen(var_content) == 0) //empty string
		new_node->env_value = strdup("");
    else
	{
		new_node->env_value = strdup(var_content);
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

t_env *dup_env(t_env *env)
{
	t_env	*head;
	t_env	*node;

	head = NULL;
	while (env != NULL)
	{
		node = env_create_node(env->env_name, env->env_value);
		if (node == NULL)
			return (NULL);
		env_add_node(&head, node);
		env = env->next;
	}
	return (head);
}

t_env *sort_env(t_env *env)
{
    t_env *sorted;
    
    sorted = dup_env(env);
    if (sorted == NULL)
        printf("export(): sorted - env deleted?\n");
    sort_lst(&sorted);
    return sorted;
}

void free_env_list(t_env *head) 
{
    t_env *current;
    t_env *next_node;

    current = head;
    while (current != NULL) 
    {
        next_node = current->next;
        free(current->env_name); // Free the duplicated env_name
        free(current->env_value); // Free the duplicated env_value
        free(current); // Free the node itself
        current = next_node;
    }
}

void no_arg_export(t_env *env)
{
    t_env *sorted;
    t_env *temp;

    sorted = sort_env(env);
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

int main() {
    // Example usage
    t_env *env_list = create_node("USER", "john");
    env_list->next = create_node("HOME", "/home/john");
    env_list->next->next = create_node("SHELL", "/bin/bash");
    env_list->next->next->next = create_node("PATH", "/usr/bin:/bin");
	env_list->next->next->next->next = create_node("EMPTY", "");
	env_list->next->next->next->next->next = create_node("UNASSIGNED", NULL);
	env_list->next->next->next->next->next->next = create_node("RANDOM", "random");

    printf("Before formatting:\n");
    print_list(env_list);

	printf("After formatting:\n");
    no_arg_export(env_list);
	

    // Free memory (not shown here for brevity)
    return 0;
}


