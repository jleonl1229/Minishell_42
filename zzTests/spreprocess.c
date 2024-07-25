/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_sh_data
{
    char    *prev_line; //last line saved to history
    char *new_line; //user inputed command with spaces around special chars
}   t_sh_data;

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

static size_t	count_substrings(const char *s, char c, int in_dquotes, int in_squotes)
{
	size_t	count;
	int		in_substring;

	count = 0;
	in_substring = 0;
	while (*s != '\0')
	{
		if (*s == '\"' && !in_squotes)
			in_dquotes = !in_dquotes;
		else if (*s == '\'' && !in_dquotes)
			in_squotes = !in_squotes;
		if (*s == c && !in_dquotes && !in_squotes)
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

static size_t	count_char(const char *s, char c)
{
	size_t	count;
	int		in_dquotes;
	int		in_squotes;

	count = 0;
	in_dquotes = 0;
	in_squotes = 0;
    while (s[count] != '\0' && (s[count] != c || in_dquotes || in_squotes))
    {
        if (s[count] == '\"' && !in_squotes)
            in_dquotes = !in_dquotes;
        else if (s[count] == '\'' && !in_dquotes)
            in_squotes = !in_squotes;
        count++;
    }
	return (count);
}*/

/*modified ft_split to ignore the char c parameter 
if it is inside quotes
*/
/*char	**ft_split_quotes(const char *s, char c)
{
	char	**pointer;
	size_t	substrings;
	size_t	i;
	size_t	substr_length;

	i = 0;
	substr_length = 0;
	substrings = count_substrings(s, c, 0, 0);
	pointer = malloc(sizeof(char *) * (substrings + 1));
	if (pointer == NULL)
		return (NULL);
	while (i < substrings)
	{
		while (*s == c)
			s++;
		substr_length = count_char(s, c);
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

void skip_quotes(char *str, int *index) 
{
    char quote_char;
	
	quote_char = str[*index];
    (*index)++;
    while (str[*index] != '\0' && str[*index] != quote_char)
        (*index)++;
}

int count_segments(char *str) 
{
    int count;
    int i;
	
    count = 1;
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\'' || str[i] == '\"')
            skip_quotes(str, &i);
        if (str[i] == '|')
            count++;
        i++;
    }
    return count;
}

char **split_by_pipe(char *line, int start, int segment_index, int i) 
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

int is_special_char(char c) 
{
    return c == '|' || c == '<' || c == '>';
}


int new_line_length(char *line, int len, int in_dquote, int in_squote)
{
    int i;
    int new_len;

    i = 0;
    new_len = 0;
    while (i < len) 
    {
        if (line[i] == '\'' && !in_dquote)
            in_squote = !in_squote;
        else if (line[i] == '\"' && !in_squote)
            in_dquote = !in_dquote;
        if (!in_squote && !in_dquote && is_special_char(line[i])) 
        {
            if (i > 0 && line[i - 1] != ' ' && !is_special_char(line[i-1]))
                new_len++;
            new_len++;
            if (i < len - 1 && line[i + 1] != ' ' && !is_special_char(line[i+1]))
                new_len++;
        } 
        else
            new_len++;
        i++;
    }
    return new_len;
}


// Function to preprocess the input string
void fill_new_line(char **new_line, char *line, int in_squote, int in_dquote)
 {
    int i;
    int j;
    int len;
    
    i = 0;
    j = 0;
    len = ft_strlen(line);
    while (i < len)
    {
        if (line[i] == '\'' && !in_dquote)
            in_squote = !in_squote;
        else if (line[i] == '\"' && !in_squote)
            in_dquote = !in_dquote;
        if (!in_squote && !in_dquote && is_special_char(line[i]))
        {
            if (i > 0 && line[i - 1] != ' ' && !is_special_char(line[i-1]))
                (*new_line)[j++] = ' ';
            (*new_line)[j++] = line[i];
            if (i < len - 1 && line[i + 1] != ' ' && !is_special_char(line[i+1]))
                (*new_line)[j++] = ' ';
        } 
        else
            (*new_line)[j++] = line[i];
        i++;
    }
    (*new_line)[j] = '\0';
}

void add_space(t_sh_data *sh, char *line)
{
    int new_len;
    char *new_line;
    int len;

    len = ft_strlen(line);
    new_len = new_line_length(line, len, 0, 0);
    printf("len is: %d\n", len);
    printf("new_len is: %d\n", new_len);
    new_line = malloc(new_len + 1);
    if (new_line == NULL)
        exit(1);
    fill_new_line(&new_line, line, 0, 0);
    sh->new_line = new_line;

}

int main() 
{
    t_sh_data *sh = (t_sh_data *)malloc(sizeof(t_sh_data));
    if (sh == NULL) {
        fprintf(stderr, "Memory allocation failed for sh\n");
        return 1;
    }
    char *input ="<infile.txt \"                   cat\"";
    add_space(sh, input);
    printf("Original: %s\n", input);
    printf("Preprocessed: %s\n", sh->new_line);
	char **segments = split_by_pipe(sh->new_line, 0, 0, 0);
	int i;
	char **split_spaces = ft_split_quotes(segments[0], ' ');

	for (i = 0; segments[i] != NULL; i++) {
		printf("segment %d: %s\n", i, segments[i]);
    }
	printf("segment %d: %s\n", i, segments[i]);

	for (i = 0; split_spaces[i] != NULL; i++) {
		printf("split space %d: %s\n", i, split_spaces[i]);
    }
	printf("split space %d: %s\n", i, split_spaces[i]);

    //free_segments(segments);
    return 0;
}*/

