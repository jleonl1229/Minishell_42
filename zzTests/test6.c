#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		while (haystack[i + j] == needle[j] && needle[j] != '\0'
			&& i + j < len && haystack[i + j] != '\0')
			j++;
		if (needle[j] == '\0')
			return ((char *)&haystack[i]);
		i++;
		j = 0;
	}
	return (NULL);
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

void unset_remove_shenv(char **env, char *arg, int set)
{
    int i;

    if (ft_strnstr(env[set], arg, ft_strlen(arg)) == NULL) 
    {
        printf("set is a good idea and bad execution\n");
        return;
    }
    free(env[set]);
    i = set;
    while (env[i + 1] != NULL)
    {
        env[i] = env[i + 1];
        i++;
    }
    env[i] = NULL;
}

int main(void)
{
    // Initialize the environment variables for testing
    char *env[] = {
        strdup("USER=testuser"),
        strdup("PATH=/usr/bin"),
        strdup("HOME=/home/testuser"),
        NULL
    };
    // Test case 1: Remove an existing environment variable
    printf("Test 1: Removing 'PATH' from environment variables.\n");
   // unset_remove_shenv(env, "PATH", 1);
   // int i = 0;
    /*for (i; env[i] != NULL; i++)
    {
        printf("env[%d] = %s\n", i, env[i]);
    }
    printf("env[%d] = %s\n", i, env[i]);*/

    // Test case 2: Attempt to remove a non-existent environment variable
    printf("\nTest 2: Attempting to remove 'SHELL' which doesn't exist.\n");
    unset_remove_shenv(env, "SHELL", 2);
    for (int i = 0; env[i] != NULL; i++)
    {
        printf("env[%d] = %s\n", i, env[i]);
    }

    return 0;
}
