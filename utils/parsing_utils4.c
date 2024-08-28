#include "../minishell.h"


/*
**  struggled a lot with signals. don't know why with I couldn't make it work with line = readline 
**  or with signal() and get_next_line. finally (thanks chatgpt) done with sigaction + gnl
*/

int heredoc_to_infile(t_list *hdoc)
{
    int new_fd;
    char *line;
    struct sigaction sa;

    // Initialize sigaction struct
    sa.sa_handler = heredoc_sigint;
    sigemptyset(&sa.sa_mask);  // No signals are blocked during handler execution
    sa.sa_flags = 0;  // Use default flags

    // Register the signal handler for SIGINT
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return (-1);
    }
    signal(SIGQUIT, SIG_IGN);
    if (access("karaket.txt", F_OK) == 0)
        unlink("karaket.txt");
    while (hdoc->next != NULL) //i.e. while you're not on the last node
    {
        while (1)
        {
            write(1, "> ", 2);  // Prompt for input
            line = get_next_line(STDIN_FILENO);
            //line = readline("> ");
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
        {
            //printf("printed\n");
            return -2;
        }
        hdoc = hdoc->next;
    }
    //last node
    new_fd = open("karaket.txt", O_RDWR | O_CREAT | O_APPEND, 0666);
	if (new_fd == -1)
    {
        printf("heredoc_to_infile(): open() function failure\n");
        return -1;
    }
    //printf("in last node\n");
    while (1)
    {
        write(1, "> ", 2);  // Prompt for input
        line = get_next_line(STDIN_FILENO);
        if (signal_received)
        {
            close(new_fd);
            //signal_received = 0;  // Reset the flag for potential future uses
            return (-2);  // Exit the function with -2
        }
        //line = readline("> ");
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
        //write(new_fd, "\n",1);
        free(line);
    }
    if (close(new_fd) == -1)
    {
        printf("heredoc_to_infile(): close() function error\n");
        return -1;
    }
	new_fd = open("karaket.txt", O_RDONLY);
    //printf("karaket.txt fd is: %d\n", new_fd);
	if (new_fd == -1)
    {
        printf("heredoc_to_infile(): open(2) function error\n");
        return -1;
    }
	return (new_fd);
}

