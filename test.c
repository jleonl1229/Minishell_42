#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*typedef struct s_env
{
    char			*env_name;
    char			*env_value;
	struct s_env	*next;
}	t_env;

typedef struct s_sh_data
{
    t_env   *env_header; // pointer to the head of the linked list holding the env vars
}   t_sh_data;

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(const char *s, char c);
char	*ft_strdup(const char *s1);

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

    //Debug print statement to verify the linked list after insertion
    printf("Current environment list:\n");
    temp = *header;
    while (temp != NULL) {
        printf("Variable: %s, Value: %s\n", temp->env_name, temp->env_value);
        temp = temp->next;
    }
    printf("End of current list\n");
    
}

static size_t	ft_count_substrings(const char *s, char c)
{
	size_t	count;
	int		in_substring;

	count = 0;
	in_substring = 0;
	while (*s != '\0')
	{
		if (*s == c)
			in_substring = 0;
		else
		{
			if (in_substring == 0)
			{
				in_substring = 1;
				count++;
			}
		}
		s++;
	}
	return (count);
}

static size_t	ft_count_char(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (s[count] != c && s[count] != '\0')
		count++;
	return (count);
}

static char	**ft_free(char **pointer, size_t substrings)
{
	size_t	i;

	i = 0;
	while (i < substrings)
	{
		free(pointer[i]);
		++i;
	}
	free(pointer);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**pointer;
	size_t	substrings;
	size_t	i;
	size_t	substr_length;

	i = 0;
	substr_length = 0;
	substrings = ft_count_substrings(s, c);
	pointer = malloc(sizeof(char *) * (substrings + 1));
	if (pointer == NULL)
		return (NULL);
	while (i < substrings)
	{
		while (*s == c)
			s++;
		substr_length = ft_count_char(s, c);
		pointer[i] = malloc(sizeof(char) * (substr_length + 1));
		if (pointer[i] == NULL)
			return (ft_free(pointer, i));
		ft_strlcpy(pointer[i], s, substr_length + 1);
		s += substr_length;
		i++;
	}
	pointer[i] = NULL;
	return (pointer);
}

char	*ft_strdup(const char *s1)
{
	size_t	length;
	size_t	i;
	char	*result;

	length = ft_strlen(s1) +1;
	i = 0;
	result = malloc(length * sizeof(char));
	if (result != NULL)
	{
		while (i < length -1 && length != 1)
		{
			result[i] = s1[i];
			i++;
		}
		result[i] = '\0';
	}
	return (result);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	length;
	size_t	i;

	length = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (length);
	while (i < dstsize - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (length);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}


t_env *dup_env(char **envp)
{
    char *var_name;
    char *var_content;
    char **a_env;
    t_env *new_node;
    t_env *header;
    //not checking if envp or *envp are null because checked in env_checker, 
    //but might be good practice to do so
    header = NULL;
    while (*envp != NULL)
    {
        a_env = ft_split(*envp, '=');
        if (a_env == NULL || *a_env == NULL)
        {
            //exit with error
        }
        var_name = *a_env;
        var_content = *(++a_env);
        new_node = env_create_node(var_name, var_content);
        printf("env_name is: %s and env_value is: %s\n", new_node->env_name, new_node->env_value);
        if (new_node == NULL)
        {
            //exit with error
        }
        env_add_node(&header, new_node);
        envp++;
    }
    return header;
}

void shell_init(t_sh_data *sh, char **envp)
{
    sh->env_header = dup_env(envp); //copies envp in sh->env_header
    //printf("header points to: %s\n", (char *)sh->env_header);

}

int main(int argc, char **argv, char **envp) {
    t_sh_data sh;
    shell_init(&sh, envp);

}*/


