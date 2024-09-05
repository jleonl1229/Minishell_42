/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleon-la <jleon-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:06:22 by jleon-la          #+#    #+#             */
/*   Updated: 2024/09/05 19:29:17 by jleon-la         ###   ########.fr       */
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

void	supporting_one(t_parsed_data *header, t_sh_data *sh)
{
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
		printf("bash: exit: %s: numeric argument required\n",
			header->cmd[1]);
		exit_free(&sh);
		exit(2);
	}
}

int	mini_exit(t_parsed_data *header, t_sh_data *sh)
{
	int	i;
	int	res;

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
		supporting_one(header, sh);
	}
	printf("exit\n");
	exit_free(&sh);
	exit (0);
}
