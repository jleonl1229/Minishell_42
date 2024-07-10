/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:27:18 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/01/30 10:28:26 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	s_length;

	s_length = ft_strlen(s);
	if (s != NULL)
	{
		write(fd, s, s_length);
		write(fd, &"\n", 1);
	}
}
/*int main(void)
{
    char *str = "Hello, World!";
    int fd = 1;

    ft_putendl_fd(str, fd);

    return 0;
}*/