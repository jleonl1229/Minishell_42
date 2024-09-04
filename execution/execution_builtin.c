#include "../minishell.h"

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

void call_builtin(t_parsed_data *header, t_sh_data *sh)
{
    free(sh->last_exit_status);

    if (ft_strncmp(header->path, "echo", ft_strlen("echo")) == 0)
        sh->last_exit_status = ft_itoa(mini_echo(header));
    else if (ft_strncmp(header->path, "cd", ft_strlen("cd")) == 0)
        sh->last_exit_status = ft_itoa(mini_cd(header, sh));
    else if (ft_strncmp(header->path, "exit", ft_strlen("exit")) == 0)
        printf("sh->last_exit_status == mini_exit()\n");
    else if (ft_strncmp(header->path, "pwd", ft_strlen("pwd")) == 0)
        sh->last_exit_status = ft_itoa(mini_pwd());
    else if (ft_strncmp(header->path, "env", ft_strlen("env")) == 0)
        sh->last_exit_status = ft_itoa(mini_env(header, sh));
    else if (ft_strncmp(header->path, "export", ft_strlen("export")) == 0)
        sh->last_exit_status = ft_itoa(mini_export(header, sh));
    else if (ft_strncmp(header->path, "unset", ft_strlen("unset")) == 0)
        sh->last_exit_status = ft_itoa(mini_unset(header, sh));

}

/*
**  differentiates between a simple command and a piped command
**  and handles output redirections based on that
*/
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
/*
**  saves original stdout to restore it once the builtin is executed
**  checks if infile is invalid and handles it in that case
**  handles outfile redirections and calls the function that will call execute the builtins
*/
int execute_builtin(int fd[2], t_parsed_data **header, t_sh_data *sh)
{
    int saved_stdout;
    
    saved_stdout = dup(STDOUT_FILENO);
    if (saved_stdout == -1)
    {
        perror("dup for saving stdout");
        return -1;
    }
    if ((*header)->simple_in_redir == -1)
    {
        exec_invalid_infile(sh, fd, header);
        return 1;
    }
    builtin_redirs(fd, *header);
    call_builtin(*header, sh);
    if (dup2(saved_stdout, STDOUT_FILENO) == -1)
    {
        perror("dup2 restore stdout");
        return -1;
    }
    close(saved_stdout);
    return 0;
}
