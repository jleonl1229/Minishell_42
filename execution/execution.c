#include "../minishell.h"


/*void ft_prints(t_sh_data *sh)
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
}*/

/*void cmd_return_status(t_sh_data *sh)
{
    int i;
    char *str;

    i = 0;
    while (sh->parsed_header->cmd[i] != NULL)
    {
        //printf("in while loop\n");
        if (ft_strncmp(sh->parsed_header->cmd[i], "$?", ft_strlen(sh->parsed_header->cmd[i])) == 0)
        {
            //printf("found a %s at %d\n", sh->parsed_header->cmd[i], i);
            str = ft_itoa(sh->last_exit_status);
            free(sh->parsed_header->cmd[i]);
            sh->parsed_header->cmd[i] = ft_strdup(str);
            free(str);
        }
        i++;
    }
}*/

int is_builtin(char *cmd)
{
    const char *builtin[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
    int i;

    if (cmd == NULL)
        return 0;
    i = 0;
    while(builtin[i] != NULL)
    {
        if (ft_strncmp(cmd, builtin[i], ft_strlen(cmd)) == 0 
        && ft_strlen(cmd) == ft_strlen(builtin[i]))
            return 1;
        i++;
    }
    return 0;
}

void execute_builtin(t_sh_data *sh)
{
    if (ft_strncmp(sh->parsed_header->path, "echo", ft_strlen("echo")) == 0)
        sh->last_exit_status = ft_itoa(mini_echo(sh));
    else if (ft_strncmp(sh->parsed_header->path, "cd", ft_strlen("cd")) == 0)
        sh->last_exit_status = ft_itoa(mini_cd(sh));
    else if (ft_strncmp(sh->parsed_header->path, "exit", ft_strlen("exit")) == 0)
        printf("sh->last_exit_status == mini_exit()\n");
    else if (ft_strncmp(sh->parsed_header->path, "pwd", ft_strlen("pwd")) == 0)
        sh->last_exit_status = ft_itoa(mini_pwd());
    else if (ft_strncmp(sh->parsed_header->path, "env", ft_strlen("env")) == 0)
        sh->last_exit_status = ft_itoa(mini_env(sh));
    else if (ft_strncmp(sh->parsed_header->path, "export", ft_strlen("export")) == 0)
        sh->last_exit_status = ft_itoa(mini_export(sh));
    else if (ft_strncmp(sh->parsed_header->path, "unset", ft_strlen("unset")) == 0)
        sh->last_exit_status = ft_itoa(mini_unset(sh));

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
    //cmd_return_status(sh, sh->parsed_header->cmd);
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

/*
check why "gargantua | wc -l" returns 0 (correct) and "<gargantua | wc -l" doesn't return 0 (incorrect)
*/
void	piping(t_sh_data *sh)
{
	int		fd[2];
	pid_t	pid;
	t_parsed_data	*header;
    int status;
    int original_stdin = dup(STDIN_FILENO);

    //ft_prints(sh);
	header = sh->parsed_header;
	while (header != NULL)
	{
        if (pipe(fd) == -1)
            perror("pipe()");
        if (is_builtin(header->path) == 1)
        {
            int saved_stdout = dup(STDOUT_FILENO);
            if (saved_stdout == -1)
                perror("dup for saving stdout");
            if (header->next != NULL) //not a simple command
            {
                if (header->last_fd != -2)
                {
                    if (dup2(header->last_fd, STDOUT_FILENO) == -1)
                        perror("dup2 for builtin");
                }
                else
                {
                    if (dup2(fd[1], STDOUT_FILENO) == -1)
                        perror("dup2 for builtin");                    
                }          
            }
            else
            {
                if (header->last_fd != -2)
                {
                    if (dup2(header->last_fd, STDOUT_FILENO) == -1)
                        perror("dup2 for builtin");
                }
            }
            execute_builtin(sh);
            if (dup2(saved_stdout, STDOUT_FILENO) == -1)
                perror("dup2 restore stdout");
            close(saved_stdout);
        }
        else
        {
            //check if path is null
            if (header->path == NULL)
            {
                if (header->simple_in_redir == -1)
                    printf("bash: infile: No such file or directory\n");
                else if (header->cmd != NULL)
                {
                    //cmd_return_status(sh, sh->parsed_header->cmd);
                    printf("bash: %s: command not found\n", header->cmd[0]);
                }
                if (header->simple_in_redir > -1)
                    close(header->simple_in_redir);
                if (header->last_fd != -2)
                    close(header->last_fd);
                if (dup2(fd[0], STDIN_FILENO) == -1)
                    perror("dup2-2");
                close(fd[0]);
                close(fd[1]);
                printf("this code\n");
                free(sh->last_exit_status);
                sh->last_exit_status = ft_strdup("127");
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
            if (wait(&status) == -1)
                perror("wait()");
            if (WIFEXITED(status))
            {
                free(sh->last_exit_status);
                sh->last_exit_status = ft_itoa(WEXITSTATUS(status));
            }
        }
            close(fd[1]);
            if (dup2(fd[0], STDIN_FILENO) == -1)
                perror("dup2-3");
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
   // printf("File descriptor %d is open\n", fd);
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