#include "../minishell.h"

int heredoc_to_infile(t_list *hdoc)
{
    int new_fd;
    char *line;

    while (hdoc->next != NULL) //i.e. while you're not on the last node
    {
        while (1)
        {
            line = get_next_line(STDIN_FILENO);
            if (line == NULL)
                break ;
            if (ft_strncmp(line, hdoc->content, ft_strlen(hdoc->content))
			== 0 && line[ft_strlen(hdoc->content)] == '\n')
            {
			    free(line);
			    break ;
            }
		    free(line);
	    }
        hdoc = hdoc->next;
    }
    //last node
    new_fd = open("karaket.txt", O_RDWR | O_CREAT | O_APPEND, 0666);
	if (new_fd == -1)
		perror("heredoc_to_infile()");
    while (1)
    {
        line = get_next_line(STDIN_FILENO);
        if (line == NULL)
            break ;
        if (ft_strncmp(line, hdoc->content, ft_strlen(hdoc->content))
			== 0 && line[ft_strlen(hdoc->content)] == '\n')
        {
            free(line);
            break ;
        }
        write(new_fd, line, ft_strlen(line));
        free(line);
    }
    close(new_fd);
	new_fd = open("karaket.txt", O_RDONLY);
    printf("karaket.txt fd is: %d\n", new_fd);
	if (new_fd == -1)
		perror("new_file");
	return (new_fd);
}

