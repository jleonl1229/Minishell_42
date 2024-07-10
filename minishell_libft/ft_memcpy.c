/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 08:55:23 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/01/30 11:28:24 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t count)
{
	size_t	i;

	i = 0;
	if (src == NULL && dest == NULL)
		return (NULL);
	while (i < count)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
/*int main(void)
{
    char c[6] = "012345";
    const void *src = &c[0];
    char *dest = &c[2];
    size_t count =4 ;
    char *result;
    result = ft_memcpy(dest, src, count);
    printf("%s\n",result);
    printf("when it should be 0123\n");
    return 0;
}*/
