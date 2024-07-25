#include "../minishell.h"

int is_special_char(char c) 
{
    return c == '|' || c == '<' || c == '>';
}

/*
returns the length of the new_line, which is line's length
 + the spaces around the special chars, ignoring special
 chars inside quotes
*/
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


/*
copies the old string into a new string taking into
consideration the spaces around special chars
*/
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

/*
from "<cat<<cat|cat" to " < cat << cat | cat". Adds spaces around
special chars.
new_line is saved in the t_sh_data struct
*/
void add_space(t_sh_data *sh, char *line)
{
    int new_len;
    char *new_line;
    int len;

    len = ft_strlen(line);
    new_len = new_line_length(line, len, 0, 0);
    new_line = malloc(new_len + 1);
    if (new_line == NULL)
        exit(1);
    fill_new_line(&new_line, line, 0, 0);
    sh->new_line = new_line;
}