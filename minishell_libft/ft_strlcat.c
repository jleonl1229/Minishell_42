/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 09:04:27 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/01/30 11:30:23 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dest_length;
	size_t	src_length;

	i = 0;
	dest_length = ft_strlen(dst);
	src_length = ft_strlen(src);
	if (dstsize == 0)
		return (src_length);
	if (dstsize < dest_length)
		return (src_length + dstsize);
	while (dest_length + i < dstsize - 1 && src[i] != '\0')
	{
		dst[dest_length + i] = src[i];
		i++;
	}
	dst[dest_length + i] = '\0';
	return (dest_length + src_length);
}
/*int main(void)
{
	char dst[10] = "Hello";
	const char *src = "world";
	size_t dstsize = 10 ;
	int result = ft_strlcat(&dst[0], src, dstsize);
	printf("%i\n", result);
	printf("%s\n", dst);
}*/
