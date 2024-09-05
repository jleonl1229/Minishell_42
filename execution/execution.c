/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:56:34 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/09/05 16:28:54 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	header->next != NULL means more commands in the pipeline
*/
void	child_out_redir(t_parsed_data *header, int fd[2])
{
	if (header->next != NULL)
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
	else if (header->next == NULL)
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
**	edge cases:
**	1- command subpipe only includes invalid infile redir
**	2- command subpipe includes invalid infile redir + invalid command
**	redirections in the child process don't affect the parent! 
**	meaning that if I redirect stdout to be the pipe fd[1] in the child process,
**	I don't need to redirect it back to terminal for another child process
*/

void	child_process(t_sh_data *sh, t_parsed_data *header, int fd[2])
{
	close(fd[0]);
	if (header->simple_in_redir != -2)
	{
		if (dup2(header->simple_in_redir, STDIN_FILENO) == -1)
			perror("dup2() - child process - infile redir");
		close(header->simple_in_redir);
	}
	child_out_redir(header, fd);
	close(fd[1]);
	if (execve(header->path, header->cmd, sh->env) == -1)
		perror("execve");
}

/*
**  checks if current simple command has a null path or an invalid infile redir
**  in that case, it returns 1, forcing to reinint the piping loop
*/
int	exec_reinit_loop(t_sh_data *sh, t_parsed_data **header, int fd[2])
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
		return (1);
	}
	if ((*header)->simple_in_redir == -1)
	{
		exec_invalid_infile(sh, fd, header);
		return (1);
	}
	return (0);
}

int	exec_manage_parent(t_sh_data *sh, t_parsed_data **header, int fd[2])
{
	pid_t	pid;
	int		status;

	if (exec_reinit_loop(sh, header, fd) == 1)
		return (1);
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
	return (0);
}

/*
**	approach is to handle everything from the parent process
**	and create as little child processes as possible to avoid execve faulty calls
*/
void	piping(t_sh_data *sh)
{
	int				fd[2];
	t_parsed_data	*header;
	int				original_stdin;

	original_stdin = dup(STDIN_FILENO);
	header = sh->parsed_header;
	while (header != NULL)
	{
		if (pipe(fd) == -1)
			perror("pipe()");
		if (is_builtin(header->path) == 1)
		{
			if (execute_builtin(fd, &(header), sh) == 1)
				continue ;
		}
		else
			if (exec_manage_parent(sh, &header, fd) == 1)
				continue ;
		prepare_next_cmd(header, fd);
		header = header->next;
	}
	dup2(original_stdin, STDIN_FILENO);
	close(original_stdin);
    /*for (int fd = 0; fd <100; fd++) {
    if (fcntl(fd, F_GETFD) != -1) {
   	printf("File descriptor %d is open\n", fd);
    }
    }*/
}
