#include "../minishell.h"


/*
**  parent loop runs while hdoc is not the last hdoc
**  write(1, "\033[2D\033[K", 6) -->ANSI escape codes. Moves the cursor back two spaces 
**  and clears the line from the cursor position to the end.
*/
int intermediate_heredoc(t_list *hdoc, char *line)
{
    while (hdoc->next != NULL)
    {
        while (1)
        {
            write(1, "> ", 2);  // Prompt for input
            line = get_next_line(STDIN_FILENO);
            if (line == NULL)
            {
                write(1, "\033[2D\033[K", 6);
                write(1, "\n", 1);
                break;
            }
            if (ft_strncmp(line, hdoc->content, ft_strlen(hdoc->content))
			== 0 && line[ft_strlen(hdoc->content)] == '\n')
            {
			    free(line);
			    break ;
            }
		    free(line);
	    }
        if (signal_received == 1)
            return -2;
        hdoc = hdoc->next;
    }
    return 0;
}

/*
**  handles the final hdoc, the one that writes line to new_fd until line
**  equals the hdoc delimiter
*/
int final_hdoc(t_list *hdoc, char *line, int new_fd)
{
    while (1)
    {
        write(1, "> ", 2); 
        line = get_next_line(STDIN_FILENO);
        if (signal_received)
        {
            close(new_fd);
            return (-2);
        }
        if (line == NULL)
        {
            write(1, "\033[2D\033[K", 6);
            write(1, "\n", 1);
            break;
        }
        if (ft_strncmp(line, hdoc->content, ft_strlen(hdoc->content))
			== 0 && line[ft_strlen(hdoc->content)] == '\n')
        {
            free(line);
            break ;
        }
        write(new_fd, line, ft_strlen(line));
        free(line);
    }
    return 0;
}
/*
**  initial karaket is opened with append permits to add lines after every while loop iteration
**  hdoc is done we close karaket and open it again with new permits
*/
int prepare_karaket(int new_fd)
{
    if (close(new_fd) == -1)
    {
        printf("heredoc_to_infile(): close() function error\n");
        return -1;
    }
	new_fd = open("karaket.txt", O_RDONLY);
	if (new_fd == -1)
    {
        printf("heredoc_to_infile(): open(2) function error\n");
        return -1;
    }
	return (new_fd);

}

/*
**  flow:
**  register and activate signals, close existing karaket files, iterate through intermediate
**  hdoc delimiters until final one is reached. Then (in final_hdoc()) enter a loop that writes 
**  to karaket.txt. Update permits and return.
*/

int heredoc_to_infile(t_list *hdoc)
{
    int new_fd;
    char *line;
    
    line = NULL;
    heredoc_signals();
    if (access("karaket.txt", F_OK) == 0)
        unlink("karaket.txt");
    if (intermediate_heredoc(hdoc, line) == -2)
        return -2;
    new_fd = open("karaket.txt", O_RDWR | O_CREAT | O_APPEND, 0666);
	if (new_fd == -1)
    {
        printf("heredoc_to_infile(): open() function failure\n");
        return -1;
    }
    if (final_hdoc(hdoc, line, new_fd) == -2)
        return -2;
    return (prepare_karaket(new_fd));
}

