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

#include <stdlib.h>

extern char **environ;  

int main(void)
{
    int i = 0;
    char *env_var;

    while ((env_var = environ[i]) != NULL)
    {
        printf("%s\n", env_var);
        i++;
    }

    return (0);
}