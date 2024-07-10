/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:01:01 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/01/30 11:27:55 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	void	*result;
	size_t	i;

	result = NULL;
	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char) c)
		{
			result = &((unsigned char *)s)[i];
			return (result);
		}
		i++;
	}
	return (result);
}
/*int main(void)
{
	char s[50] = "Hola amigo";
	int c = 'a';
	size_t n = 10;
	char *result = ft_memchr(s, c, n);
	printf("%s\n", result);
}*/