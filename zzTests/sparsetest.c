/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_parsed_data
{
    char *path; //absolute path to executable
    char *cmd; //executable command, without args
    char **args; //command args
    char *simple_in_redir; //filename where stdin is redirected from
    char *simple_out_redir; //filename where stdout is redirected to
    char *here_doc; //delimiter to handle here_doc feature
    char *append; //filename to handle append redirection to stdout
    struct s_parsed_data *next;
} t_parsed_data;

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
}

char	**ft_split_quotes(const char *s, char c)
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

char **cmd_arr(char **cpy_segment)
{
    int i;
    int count;
    char **cmd;
    
    i = 0;
    count = 0;
    while (cpy_segment[i] != NULL)
    {
        if (strncmp(cpy_segment[i], "1", strlen(cpy_segment[i])) == 0)
            count++;
        i++;
    }
    cmd = (char **)malloc((count + 1) * sizeof(char *));
    if (cmd == NULL) 
        exit(1);
    printf("count is: %d\n", count);
    return cmd;
}


void parse_cmd(t_parsed_data *node, char **segment, char **cpy_segment)
{
    int i;
    int j;
    char **cmd;

    i = 0;
    j = 0;
    cmd = cmd_arr(cpy_segment);
    while(segment[i] != NULL)
    {
        if (strncmp(cpy_segment[i], "1", strlen(cpy_segment[i])) == 0)
            cmd[j++] = segment[i];
        i++;
    }
    i = 0;
    while (cmd[i] != NULL)
        remove_quotes(cmd[i++]);
    node->args = malloc(i * sizeof(char*));
    i = 0;
    node->cmd = cmd[i++];
    j = 0;
    while(cmd[i] != NULL)
        node->args[j++]= cmd[i++];
    node->args[j] = NULL;
}


char **alloc_cpy_segment(char **segment)
{
    int size;
    char **cpy_segment;

    size = 0;
    while(segment[size] != NULL)
        size++;
    cpy_segment = (char **)malloc((size + 1) * sizeof(char *));
    if (cpy_segment == NULL) 
        exit(1);
    return cpy_segment;
}

void mod_cpy_segment(char ***cpy_segment, int *i)
{
    (*cpy_segment)[*i] = strdup("0");
    (*cpy_segment)[*i + 1] = strdup("0");
    if ((*cpy_segment)[*i] == NULL || (*cpy_segment)[*i + 1] == NULL)
        exit(1);
    *i += 2;
}

void handle_redir(char *redir, char *file, t_parsed_data *parsed_data) 
{
    if (strcmp(redir, "<") == 0)
        parsed_data->simple_in_redir = file;
    else if (strcmp(redir, ">") == 0)
        parsed_data->simple_out_redir = file;
    else if (strcmp(redir, ">>") == 0)
        parsed_data->append = file;
    else if (strcmp(redir, "<<") == 0)
        parsed_data->here_doc = file;
}

char **parse_redir(t_parsed_data *parsed_data, char **segment)
 {
    int i;
    char **cpy_segment;

    i = 0;
    cpy_segment = alloc_cpy_segment(segment);
    while (segment[i] != NULL) 
    {
        if (strcmp(segment[i], "<") == 0 || strcmp(segment[i], ">") == 0
        || strcmp(segment[i], "<<") == 0 || strcmp(segment[i], ">>") == 0)
        {
            handle_redir(segment[i], segment[i+1], parsed_data);
            mod_cpy_segment(&cpy_segment, &i);
        }
        else 
        {
            cpy_segment[i] = strdup("1");
            i++;
        }
    }
    cpy_segment[i] = NULL; // Null-terminate the new array
    return cpy_segment;
}

void parse_add_node(t_parsed_data **head, t_parsed_data *new_node) 
{
    t_parsed_data *current;

    if (*head == NULL) 
        *head = new_node;
    else 
    {
        current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
    }
    new_node->next = NULL; // Ensure the new node's next pointer is set to NULL
}

t_parsed_data *parse_line(t_parsed_data *header, char **pipe_segment) 
{
    t_parsed_data *node;
	char **cpy_segment;

    node = (t_parsed_data *)malloc(sizeof(t_parsed_data));
    if (node == NULL)
        exit(1);
	node->path = NULL;
    node->cmd = NULL;
    node->args = NULL;
    node->simple_in_redir = NULL;
    node->simple_out_redir = NULL;
    node->here_doc = NULL;
    node->append = NULL;
    node->next = NULL;
    cpy_segment = parse_redir(node, pipe_segment); //fills node with redirection data
	int i = 0;
	while (cpy_segment[i] != NULL)
	{
		printf("cpy_segment %d is:%s\n", i, cpy_segment[i]);
		i++;
	}
    parse_cmd(node, pipe_segment, cpy_segment); //fills node with command data
    parse_add_node(&header, node); //add nodes to the bottom of the list

    return header;
}

int main() 
{
    t_sh_data *sh = (t_sh_data *)malloc(sizeof(t_sh_data));
    if (sh == NULL) {
        fprintf(stderr, "Memory allocation failed for sh\n");
        return 1;
    }
    t_parsed_data *header = NULL;
    char *input ="<<test echo >out hello\"wor\'ld\"\'te\"st\' >out1>out2| cat cat cat";
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

    header = parse_line(header, split_spaces);
    printf("header->cmd is: %s\n", header->cmd);
    i = 0;
    while(header->args[i] !=NULL)
    {
        printf("header->args %d is: %s\n", i, header->args[i++]);
    }
    printf("header->args %d is: %s\n", i, header->args[i]);
    printf("header->simple_in_redir is: %s\n", header->simple_in_redir);
    printf("header->simple_out_redir is: %s\n", header->simple_out_redir);
    printf("header->here_doc: %s\n", header->here_doc);
    printf("header->append is: %s\n", header->append);
    printf("header->next is: %s\n", (char *)header->next);

    return 0;
}*/


/*int main(void)
{
    t_parsed_data *node;
    char *segment[] = {
        strdup("                     echo"),
        strdup("hello\"wor\'ld\"\'te\"st\'"),
        strdup("my"),
        strdup("good"),
        strdup("friend"),
        strdup(">"),
        strdup("file1"),
        strdup(">"),
        strdup("file2"),
        strdup("<<"),
        strdup("file3"),
        NULL
    };

    char *cpy_segment[] = {
        strdup("1"),
        strdup("1"),
        strdup("1"),
        strdup("1"),
        strdup("1"),
        strdup("0"),
        strdup("0"),
        strdup("0"),
        strdup("0"),
        strdup("0"),
        strdup("0"),
        NULL
    };


    node = (t_parsed_data *)malloc(sizeof(t_parsed_data));
    if (node == NULL)
        exit(1);
	node->path = NULL;
    node->cmd = NULL;
    node->args = NULL;
    node->simple_in_redir = NULL;
    node->simple_out_redir = NULL;
    node->here_doc = NULL;
    node->append = NULL;
    node->next = NULL;
    parse_cmd(node, segment, cpy_segment);

    return 0;
}*/
