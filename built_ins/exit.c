/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:06:22 by jleon-la          #+#    #+#             */
/*   Updated: 2024/09/05 17:26:11 by mzuloaga         ###   ########.fr       */
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

int	mini_exit(t_parsed_data *header, t_sh_data *sh)
{
	int	i;
	int	res;

	i = 0;
    if (is_simple_cmd(sh) != 1)
        return (ft_atoi(sh->last_exit_status));
    //if exit has args
    if (header->cmd[1] != NULL)
    {
        printf("exit\n");
        //if exit has more than 1 arg
        if (header->cmd[2] != NULL)
        {
            printf("bash: exit: too many arguments\n");
            free(sh->last_exit_status);
            return 1;
        }
        //check if arg is numeric
        if (header->cmd[1][i] == '+' || header->cmd[1][i] == '-')
            i++;
        while (header->cmd[1][i] != '\0')
        {
            if (ft_isdigit(header->cmd[1][i]) != 1)
                break;
            i++;
        }
        //is numeric
        if (header->cmd[1][i] == '\0')
        {
            if (header->cmd[1][0] == '-')
            {
                res = 256 - (ft_atoi(header->cmd[1]) % 256);
                exit_free(&sh);
                exit(res);
                //return (256 - (ft_atoi(header->cmd[1]) % 256));
            }
            res = ft_atoi(header->cmd[1]) % 256;
            exit_free(&sh);
            exit(res);
            //return (ft_atoi(header->cmd[1]) % 256);
        }
        else
        {
            printf("bash: exit: %s: numeric argument required\n", header->cmd[1]);
            exit_free(&sh);
            exit(2);
            //return 2;
        }
    }
    //exit has no args
    printf("exit\n");
    exit_free(&sh);
    exit (0);
    //return (0);

}

