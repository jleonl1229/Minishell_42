/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleon-la <jleon-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:20:11 by jleon-la          #+#    #+#             */
/*   Updated: 2024/07/08 16:30:00 by jleon-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**  what happens if user creates an env? will sh->env be updated and hold that variable?
**  likely not, so need to think about how to solve that
*/
int	mini_env(t_sh_data *sh)
{
    t_env *temp;
    if (sh->parsed_header->cmd[1] != NULL)
    {
        printf("Usage: env\n");
        return 1;
    }
    if (sh == NULL || sh->env == NULL)
        return 1;
    temp = sh->env_header;
    while (temp != NULL)
    {
        if (temp->env_value != NULL)
            printf("%s=%s\n", temp->env_name, temp->env_value);
        temp = temp->next;
    }
    return 0;
}
