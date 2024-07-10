/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 12:56:37 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/01/30 11:30:34 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	length;

	i = 0;
	length = ft_strlen(s);
	while (i <= length)
	{
		if (s[i] == (unsigned char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	return (NULL);
}
/*int main(void)
{
    const char *s = "hola amigo";
    int c = 'a';
    char *result = ft_strchr(s, c);
    printf("%s\n", result);
}*/