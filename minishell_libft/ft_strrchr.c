/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 08:47:32 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/01/30 11:31:12 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	length;

	length = ft_strlen(s);
	if (c >= 256)
		c = c % 256;
	if (c == '\0')
		return ((char *)&s[length]);
	while (length > 0)
	{
		length--;
		if (s[length] == c)
		{
			return ((char *)&s[length]);
		}
	}
	return (NULL);
}
/*int main(void)
{
    const char *s = "bo";
    int c = 1024 + 'e';
    char *result = ft_strrchr(s, c);
    printf("%s\n", result);
}*/