#include "../minishell.h"


void ft_prints(t_sh_data *sh)
{
    int i;
    t_parsed_data *ph = sh->parsed_header;
        while(ph != NULL)
        {
            printf("parsed_header->path is: %s\n", ph->path);
            i = 0;
            if (ph->cmd != NULL)
            {
                while(ph->cmd[i] != NULL)
                {
                    printf("ph->cmd %d is: %s\n", i, ph->cmd[i]);
                    i++;
                }
            }
            printf("ph->simple_in_redir is: %d\n", ph->simple_in_redir);
            printf("ph->last_fd is: %d\n", ph->last_fd);
            t_list *temp;
            temp = ph->here_doc;
            while (temp != NULL)
            {
                printf("ph->here_doc is: %s\n", (char *)temp->content);
                temp = temp->next;
            }
            printf("ph->here_doc is: %p\n", temp);
            printf("ph->next is: %p\n", (void *)ph->next);      
            printf("ph is %p\n", ph);     
            ph = ph->next;
            printf("sh->parsed_header is: %p\n", sh->parsed_header);
        }
}

/*
edge cases:
1- command subpipe only includes invalid infile redir
2- command subpipe includes invalid infile redir + invalid command
*/

/*redirections in the child process don't affect the parent! meaning that if I redirect stdout to be
the pipe write end in the child process, I don't need to redirect it back to terminal for another child process*/

void	child_process(t_sh_data *sh, t_parsed_data *header, int fd[2])
{
	close(fd[0]);
    //infile
    if (header->simple_in_redir != -2)
    {
        if (dup2(header->simple_in_redir, STDIN_FILENO) == -1)
            perror("dup2() - child process - infile redir");
        close(header->simple_in_redir);
    }
    //outfile redir
	if (header->next != NULL) //more commands in the pipeline
	{
        if (header->last_fd != -2)
        {
            if (dup2(header->last_fd, STDOUT_FILENO) == -1)
                perror("dup2() - child process - last_fd stdout1");
            close(header->last_fd);
        }
		else
        {
            if (dup2(fd[1], STDOUT_FILENO) == -1)
                perror("dup2() - child process - fd[1] stdout");
        }
	}
	else if (header->next == NULL) //last command
	{
        if (header->last_fd != -2)
        {
            if (dup2(header->last_fd, STDOUT_FILENO) == -1)
                perror("dup2() - child process - last_fd stdout2");
            close(header->last_fd);
        }
	}
	close(fd[1]);
    if (execve(header->path, header->cmd, sh->env) == -1)
        perror("execve");

}



/*
my current approach is to not create child processes unnecesarily. for example: if path is null,
I can't call execve, I would have to exit/kill the child process prematurely. But remember that
the child process forks the parents code too, and I don't want the child executing the parent's code
so I need to kill the child process (what I achieve with execve and its "hijacking" of the program image).
I can kill a process child by calling the kill function or by calling the exit function. Issue with exiting is
that valgrind will output the leaks summary (valgrind does a report per process), so I'd likely have to
free everything before calling the exit function (can be very tough).

Therefore, I'm trying by all means to handle everything from the parent process, so I don't need to 
prematurely exit the child process
*/
void	piping(t_sh_data *sh)
{
	int		fd[2];
	pid_t	pid;
	t_parsed_data	*header;
    int original_stdin = dup(STDIN_FILENO);

    ft_prints(sh);
	header = sh->parsed_header;
	while (header != NULL)
	{
		if (pipe(fd) == -1)
			perror("pipe()");
        //check if path is null
        if (header->path == NULL)
        {
            if (header->simple_in_redir == -1)
                printf("bash: infile: No such file or directory\n");
            else if (header->cmd != NULL)
                printf("bash: %s: command not found\n", header->cmd[0]);
            if (header->simple_in_redir > -1)
                close(header->simple_in_redir);
            if (header->last_fd != -2)
                close(header->last_fd);
		    if (dup2(fd[0], STDIN_FILENO) == -1)
			    perror("dup2-2");
            close(fd[0]);
            close(fd[1]);
            header = header->next;
            continue;
        }
        //check if simple_in_redir == -1
        if (header->simple_in_redir == -1)
        {
            printf("bash: infile: No such file or directory\n");
            if (dup2(fd[0], STDIN_FILENO) == -1)
			    perror("dup2-2");
            close(fd[0]);
            close(fd[1]);
            header = header->next;
            continue;
        }
		pid = fork();
		if (pid == -1)
			perror("fork()");
		if (pid == 0)
			child_process(sh, header, fd);
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			perror("dup2-3");
		if (wait(NULL) == -1)
			perror("wait()");
		close(fd[0]);
        if (header->simple_in_redir > -1)
            close(header->simple_in_redir);
        if (header->last_fd != -2)
            close(header->last_fd);
        if (access("karaket.txt", F_OK) == 0)
        {
            if (unlink("karaket.txt") == -1) //removing here_doc temporary file
			    perror("unlink() here_doc");
        }
		header = header->next;
	}
    dup2(original_stdin, STDIN_FILENO);
    close(original_stdin);
    for (int fd = 0; fd <100; fd++) {
    if (fcntl(fd, F_GETFD) != -1) {
    printf("File descriptor %d is open\n", fd);
    }
    }
}



/* printf("header->path is: %s\n", header->path);
    int k = 0;
    while(header->cmd[k] != NULL)
    {
        printf("header->cmd[%d] is %s\n", k, header->cmd[k]);
        k++;
    }
    printf("header->cmd[%d] is %s\n", k, header->cmd[k]);
    k = 0;
    while(sh->env[k] != NULL)
    {
        printf("sh->env[%d] is %s\n", k, sh->env[k]);
        k++;
    }
    printf("sh->env[%d] is %s\n", k, sh->env[k]);*/