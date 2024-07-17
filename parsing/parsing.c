#include "../minishell.h"

/*
split command line into pipe segments
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
}*/


/*int parsing(char *line)
{
	char **pipe_segments;
	int i;
	char **split_space;

	i = 0;
	pipe_segments = split_by_pipe(line, 0, 0, 0);
	//if(pipe_segments == NULL)
		//something
	while(pipe_segments[i] != NULL)
	{
		split_space = ft_split(pipe_segments[i], ' '); //ft_split not working properly because it doesn't take into account spaces inside quotes
		//detect redirections

	}
}*/