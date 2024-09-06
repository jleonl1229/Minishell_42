/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:06:22 by jleon-la          #+#    #+#             */
/*   Updated: 2024/09/06 14:16:07 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**  free_parsing_list -> frees t_parsed_data
**  free_env_list -> frees t_env data
*/
void	exit_free(t_sh_data **sh)
{
	free_parsing_list(sh);
	free_env_list((*sh)->env_header);
	free_matrix((*sh)->env);
	free((*sh)->prev_line);
	free((*sh)->new_line);
	free((*sh)->last_exit_status);
	free((*sh));
}

void	numeric_exit(t_parsed_data *header, t_sh_data *sh, int i)
{
	int	res;

	if (header->cmd[1][i] == '\0')
	{
		if (header->cmd[1][0] == '-')
		{
			res = 256 - (ft_atoi(header->cmd[1]) % 256);
			exit_free(&sh);
			exit(res);
		}
		res = ft_atoi(header->cmd[1]) % 256;
		exit_free(&sh);
		exit(res);
	}
	else
	{
		printf("bash: exit: %s: numeric argument required\n", header->cmd[1]);
		exit_free(&sh);
		exit(2);
	}
}

/*
**  if exit is not used as a simple command (example: ls | exit)
**  returns the previous command's exit status
**  checks if it has args (and if it has more than 1), if args are numeric
**  returns arg % 256 (1 byte possible solutions)
*/
int	mini_exit(t_parsed_data *header, t_sh_data *sh)
{
	int	i;

	i = 0;
	if (is_simple_cmd(sh) != 1)
		return (ft_atoi(sh->last_exit_status));
	if (header->cmd[1] != NULL)
	{
		printf("exit\n");
		if (header->cmd[2] != NULL)
			return (printf("bash: exit: too many arguments\n"),
				free(sh->last_exit_status), 1);
		if (header->cmd[1][i] == '+' || header->cmd[1][i] == '-')
			i++;
		while (header->cmd[1][i] != '\0')
		{
			if (ft_isdigit(header->cmd[1][i]) != 1)
				break ;
			i++;
		}
		numeric_exit(header, sh, i);
	}
	printf("exit\n");
	exit_free(&sh);
	exit (0);
}
