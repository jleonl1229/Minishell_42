/*#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	length;
	size_t	i;

	if (src == NULL)
		length = 0;
	else
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

int main(void)
{

	//input HOME$HOME;
	//
    int var_len = 7;
    int start = 1;
    char *var_name = malloc (var_len - start + 1);
    char *s2 = strdup("TOBIAS");
    strncpy(var_name, s2, var_len - start);
    var_name[var_len - start] = '\0';
    printf("var_name is: %s\n", var_name);
    printf("1 ft_strlen is: %ld\n", ft_strlen(var_name));

    int var_len2 = 7;
    int start2 = 1;
    char *var_name2 = malloc (var_len2 - start2 + 1);
    char *s22 = strdup("TOBIAS");
    ft_strlcpy(var_name2, s22, var_len2 - start2 + 1);
    //var_name2[var_len2 - start2] = '\0';
    printf("var_name2 is: %s\n", var_name2);
    printf("2 ft_strlen is: %ld\n", ft_strlen(var_name2));
}*/
