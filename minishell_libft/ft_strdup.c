/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:13:18 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/01/30 16:48:09 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	length;
	size_t	i;
	char	*result;

	length = ft_strlen(s1) +1;
	i = 0;
	result = malloc(length * sizeof(char));
	if (result != NULL)
	{
		while (i < length -1 && length != 1)
		{
			result[i] = s1[i];
			i++;
		}
		result[i] = '\0';
	}
	return (result);
}
/*int main(void)
{
	const char *s1 = "hola amigo";
	char *result = NULL;
	result = ft_strdup(s1);
	printf("%s\n", result);
	return 0;
}*/