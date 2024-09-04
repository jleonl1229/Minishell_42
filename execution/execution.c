/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:56:34 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/09/04 16:00:52 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


/*
**  dup2 prepares next simple command to read from the pipe
**  without this code "<noinfile ls| wc -l" wouldn't return 0 (and it needs to, per Bash)
*/
void    exec_invalid_infile(t_sh_data *sh, int fd[2], t_parsed_data ** header)
{
    printf("bash: infile: No such file or directory\n");
    if (dup2(fd[0], STDIN_FILENO) == -1)
        perror("dup2-2");
    close(fd[0]);
    close(fd[1]);
    free(sh->last_exit_status);
    sh->last_exit_status = ft_strdup("1");
    *header = (*header)->next;
}

void child_out_redir(t_parsed_data *header, int fd[2])
{
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
	child_out_redir(header, fd);
	close(fd[1]);
    //cmd_return_status(sh, sh->parsed_header->cmd);
    if (execve(header->path, header->cmd, sh->env) == -1)
        perror("execve");

}
/*
**  checks if current simple command has a null path or an invalid infile redir
**  in that case, it returns 1, forcing to reinint the piping loop
*/
int exec_reinit_loop(t_sh_data *sh, t_parsed_data **header, int fd[2])
{
    if ((*header)->path == NULL)
    {
        if ((*header)->simple_in_redir == -1)
            printf("bash: infile: No such file or directory\n");
        else if ((*header)->cmd != NULL)
            printf("bash: %s: command not found\n", (*header)->cmd[0]);
        if ((*header)->simple_in_redir > -1)
            close((*header)->simple_in_redir);
        if ((*header)->last_fd != -2)
            close((*header)->last_fd);
        if (dup2(fd[0], STDIN_FILENO) == -1)
            perror("dup2-2");
        close(fd[0]);
        close(fd[1]);
        free(sh->last_exit_status);
        sh->last_exit_status = ft_strdup("127");
        *header = (*header)->next;
        return 1;
    }
        if ((*header)->simple_in_redir == -1)
        {
            exec_invalid_infile(sh, fd, header);
            return 1;
        }
        return 0;
}

int exec_manage_parent(t_sh_data *sh, t_parsed_data **header, int fd[2])
{
    pid_t pid;
    int status;

    if (exec_reinit_loop(sh, header, fd) == 1)
        return 1;
    pid = fork();
    if (pid == -1)
        perror("fork()");
    if (pid == 0)
        child_process(sh, *header, fd);
    if (wait(&status) == -1)
        perror("wait()");
    if (WIFEXITED(status))
    {
        free(sh->last_exit_status);
        sh->last_exit_status = ft_itoa(WEXITSTATUS(status));
    }
    return 0;
}

void prepare_next_cmd(t_parsed_data *header, int fd[2])
{
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
    t_parsed_data *header;
    int original_stdin;

    original_stdin = dup(STDIN_FILENO);
    header = sh->parsed_header;
	while (header != NULL)
	{
        if (pipe(fd) == -1)
            perror("pipe()");
        if (is_builtin(header->path) == 1)
        {
            if (execute_builtin(fd, &(header), sh) == 1)
                continue;
        }
        else
            if (exec_manage_parent(sh, &header, fd) == 1)
                continue;
        prepare_next_cmd(header, fd);
        header = header->next;
    }
    dup2(original_stdin, STDIN_FILENO);
    close(original_stdin);
    for (int fd = 0; fd <100; fd++) {
    if (fcntl(fd, F_GETFD) != -1) {
   //printf("File descriptor %d is open\n", fd);
    }
    }
}

