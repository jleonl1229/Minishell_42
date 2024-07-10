/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:20:42 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/01/30 11:40:47 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	blocksize;
	void	*result;
	size_t	i;

	blocksize = count * size;
	result = malloc(blocksize);
	i = 0;
	if (result != NULL)
	{
		while (i < blocksize)
		{
			((unsigned char *)result)[i] = '\0';
			i++;
		}
	}
	return (result);
}
/*int main(void)
{
	int *result = NULL;
	int count = 10;
	result = ft_calloc(count, sizeof(int));
	int i = 0;
	while(i < count)
	{
		printf("%i", result[i]);
		i++;
	}
	printf("\n");
	return 0;
}*/