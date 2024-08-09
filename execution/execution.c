#include "../minishell.h"



void child_process(t_sh_data *sh)
{
    close(fd[0]);
    if(header->next != NULL)
    {
        if(dup2(fd[1], STDOUT_FILENO) == -1)
            cleanup(clarg, DUP2, NULL);
    }
    else if (header->next == NULL)
    {
        if(dup2(clarg->outfile_fd, STDOUT_FILENO) == -1)
            cleanup(clarg, DUP2, NULL);
    }
    close(fd[1]);
    close(clarg->outfile_fd);
    if (execve(header->path_cmd, header->cmd, envp) == -1)
        cleanup(clarg, EXECVE, NULL);
}

void piping(t_sh_data *sh)
{
    int fd[2];
    pid_t pid;
    t_parsed_data *header;

    header = sh->parsed_header;
	if (header->simple_in_redir == -1) //printf error and traverse to last node in linked list to execute that command
	{
		printf("bash: infile: No such file or directory\n");
		while(header->next != NULL)
			header = header->next;
	}
	if (header->simple_in_redir == -1) //if last command also has an infile error, exit
		exit(1); // \<noinfile echo "hello"\, fr example, prints error and doesn't print "hello", so exit
	if (header->simple_in_redir != -2) //-2 would mean no infile redir has happened, so no need to dup2
	{
		if (dup2(header->simple_in_redir, STDIN_FILENO) == -1)
			exit(1);
		close(header->simple_in_redir); //to avoid duplicates
	}
    while (header != NULL) //if not single command
    {
        if (pipe(fd) == -1)
            exit(1);
        pid = fork();
        if (pid == -1)
            exit(1);
        if (pid == 0)
            child_process(sh);
        close(fd[1]); //parent process won't be writing
        if (dup2(fd[0], STDIN_FILENO) == -1) //prepare 
            cleanup(clarg, DUP2, NULL);
        wait(NULL); //handle error?
        close(fd[0]); 
        header = header->next;
    }
}