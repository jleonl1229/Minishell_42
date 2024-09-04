#include "../minishell.h"




/*int is_builtin(char *cmd)
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
    free(sh->last_exit_status);

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

void    exec_invalid_infile(int fd[2], t_parsed_data ** head)
{
    printf("bash: infile: No such file or directory\n");
    if (dup2(fd[0], STDIN_FILENO) == -1)
        perror("dup2-2");
    close(fd[0]);
    close(fd[1]);
    head = head->next;
}

void builtin_redirs(int fd[2], t_parsed_data *header)
{
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
}

int execute_builtin(int fd[2], t_parsed_data **head)
{
    int saved_stdout;
    
    saved_stdout = dup(STDOUT_FILENO);
    if (saved_stdout == -1)
    {
        perror("dup for saving stdout");
        return -1;
    }
    if (header->simple_in_redir == -1)
    {
        exec_invalid_infile(fd, &header);
        return 1;
    }
    builtin_redirs(fd, header);
    call_builtin(sh);
    if (dup2(saved_stdout, STDOUT_FILENO) == -1)
    {
        perror("dup2 restore stdout");
        return -1;
    }
    close(saved_stdout);
    return 0;
}



void	piping(t_sh_data *sh)
{
	int		fd[2];
	pid_t	pid;
	t_parsed_data	*header;
    int status;
    int original_stdin = dup(STDIN_FILENO);

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
}*/




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