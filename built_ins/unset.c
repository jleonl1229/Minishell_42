/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleon-la <jleon-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:27:46 by jleon-la          #+#    #+#             */
/*   Updated: 2024/07/08 16:30:35 by jleon-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int main(int ac, char **av)
{
    int i;

    i = 0;
    if  (ac >= 2)
    {
        while (i < ac)
        {
            // Here the progrma must delete specified environment variables
        }
    }
    else
        return (fd_printf(2, "unset: not enough arguments\n"), 1)
    return (0);
}