#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void skip_quotes(char *str, int *index) {
    char quote_char;
	
    quote_char = str[*index];
    (*index)++;
    while (str[*index] != '\0' && str[*index] != quote_char)
        (*index)++;
    if (str[*index] == quote_char) //skip closing quote
        (*index)++;
}

// Function to count the number of segments
int count_segments(char *str) 
{
    int count;
	int i;
	
	count = 1;
	i = 0;
    while (str[i] != '\0')
	{
        if (str[i] == '\'' || str[i] == '"')
            skip_quotes(str, &i);
        if (str[i] == '|')
            count++;
		i++;
    }
    return count;
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
}*/

/*Function to split the string by pipe. start, segment_index and i
are passed as function parameters to save on lines needed by the function.
default value is 0 for the 3 of them.
*/
/*char **split_by_pipe(char *line, int start, int segment_index, int i) 
{
    int segments;
    char **result;

	segments = count_segments(line);
	result = malloc((segments + 1) * sizeof(char *));
	if (result == NULL)
	{
		//error
	}
    while(segment_index < segments) 
	{
        if (line[i] == '\'' || line[i] == '"')
            skip_quotes(line, &i);
        if (line[i] == '|' || line[i] == '\0')
		{
            result[segment_index] = malloc((i - start + 1) * sizeof(char));
			if(result[segment_index] == NULL)
			{
				//error
			}
            ft_strlcpy(result[segment_index], line + start, i - start + 1);
            segment_index++;
            start = i + 1;
        }
		i++;
    }
    result[segments] = NULL;
    return result;
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

// Function to free the allocated memory
void free_segments(char **segments) {
    int i = 0;
    while (segments[i] != NULL) 
	{
        free(segments[i]);
        i++;
    }
    free(segments);
}

// Test the function
int main() {
    char *input = "echo \"<hello, world\" > out | < out cat";
    char **segments = split_by_pipe(input, 0, 0, 0);
	int i;
	char **split_spaces = ft_split(segments[0], ' ');

    for (i = 0; segments[i] != NULL; i++) {
		
        printf("Segment %d: %s\n", i, segments[i]);
    }
	printf("Segment %d: %s\n", i, segments[i]);

	for (i = 0; split_spaces[i] != NULL; i++) {
		printf("split space %d: %s\n", i, split_spaces[i]);
    }
	printf("split space %d: %s\n", i, split_spaces[i]);

    free_segments(segments);
    return 0;
}*/

