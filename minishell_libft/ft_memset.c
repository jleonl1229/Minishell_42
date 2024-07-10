/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:18:05 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/01/30 11:35:00 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((char *)b)[i] = (unsigned char) c;
		i++;
	}
	return (b);
}
/*int main(void)
{
	void *b = NULL;
	int c = 'a';
	size_t len = 10;
	b = malloc(len * sizeof(char)); // para testar
	void *result = ft_memset(b, c, len);
	printf("%s\n", result);
}*/