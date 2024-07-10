/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:48:31 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/01/30 11:30:25 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	s1_length;
	size_t	s2_length;
	char	*result;

	if (s1 != NULL && s2 != NULL)
	{
		s1_length = ft_strlen(s1);
		s2_length = ft_strlen(s2);
		result = ft_calloc(s1_length + s2_length +1, sizeof(char));
		if (result != NULL)
		{
			ft_memcpy(result, s1, s1_length);
			ft_strlcat(result, s2, s1_length + s2_length + 1);
			return (result);
		}
	}
	return (NULL);
}

/*int main(void)
{
	const char *s1 = "";
	const char *s2 = "";
	char *result = ft_strjoin(s1,s2);
	printf("%s\n", result);
	return 0;
}*/
