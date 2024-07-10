/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:58:24 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/01/30 11:30:14 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	f(unsigned int i, char c)
{
	return (i + c);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	size_t	s_length;
	size_t	i;

	if (s == NULL)
		return (NULL);
	s_length = ft_strlen(s);
	i = 0;
	result = ft_calloc(s_length + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	while (i < s_length)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	return (result);
}
/*int main(void)
{
    char const *s = "abc";
    char *result = ft_strmapi (s, f);
    printf("%s\n", result);
    return (0);
}*/