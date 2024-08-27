#include <stdlib.h>
#include <stdio.h>
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

int main(void)
{
    char *res1;
    char *res2;
    char *haystack = "hola_LAST_EXIT_STATUS_";
    char *needle = "_LAST_EXIT_STATUS_";
    res1 = strstr(haystack, needle);
    res2 = ft_strnstr(haystack, needle, ft_strlen(haystack));
    printf("res1 is: %s\n", res1);
    printf("res2 is: %s\n", res2);
    printf("res1 strlen is: %ld\n", ft_strlen(res1));
    printf("res2 strlen is: %ld\n", ft_strlen(res2));
    return 0;

}


