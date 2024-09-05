/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:19:40 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/09/05 16:29:13 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**  dup2 prepares next simple command to read from the pipe
**  without this code "<noinfile ls| wc -l" wouldn't return 0 (and it needs to, 
**  per Bash)
*/
void	exec_invalid_infile(t_sh_data *sh, int fd[2], t_parsed_data **header)
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

void	prepare_next_cmd(t_parsed_data *header, int fd[2])
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
		if (unlink("karaket.txt") == -1)
			perror("unlink() here_doc");
	}
}
