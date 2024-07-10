/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:36:24 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/01/30 11:31:04 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*result;
	size_t	s_length;

	i = 0;
	s_length = ft_strlen(s);
	if (start >= s_length)
		len = 0;
	if (len > s_length - start)
		len = s_length - start;
	result = malloc(len + 1);
	if (result != NULL && s != NULL)
	{
		while (i < len)
		{
			result[i] = s[start];
			i++;
			start++;
		}
		result[i] = '\0';
		return (result);
	}
	return (NULL);
}
/*int main(void)
{
	char const *s = "hola amigo";
	unsigned int start = 300;
	size_t len = 5;
	char *result = ft_substr(s, start, len);
	printf("%s\n", result);
	return 0;
}*/