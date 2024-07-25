#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*typedef struct s_sh_data
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
    char *input = "<cat<infile.txt<<outfile";
    add_space(sh, input);
    printf("Original: %s\n", input);
    printf("Preprocessed: %s\n", sh->new_line);
    return 0;
}*/