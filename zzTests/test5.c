/*#include <stdio.h>
#include <string.h>
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

void	remove_quotes(char *element)
{
	int	i;
	int	in_dquotes;
	int	in_squotes;

	i = 0;
	in_dquotes = 0;
	in_squotes = 0;
	printf("element length is: %ld\n", strlen(element));
	while (element[i]) //hello"wor'ld"'te"st'
	{
		if (element[i] == '\"' && in_squotes == 0)
		{
			in_dquotes = !in_dquotes;
			ft_strlcpy(&element[i], (const char *)&element[i + 1], ft_strlen(&element[i]));
			continue; //skips the "i++" 
		}
		else if (element[i] == '\'' && in_dquotes == 0)
		{
			in_squotes = !in_squotes;
			ft_strlcpy(&element[i], (const char *)&element[i + 1], ft_strlen(&element[i]));
			continue;
		}
		i++;
	}
	printf("element length is: %ld\n", strlen(element));

}

int main() {
    // Example input array of modifiable strings
    char *test = strdup("hello\"wor'ld\"'te\"st'");

    printf("Before:\n");
	printf("test is: %s\n", test);

    remove_quotes(test);

    printf("\nAfter:\n");
	printf("test is: %s\n", test);

    return 0;
}*/
