/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:18:57 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/01/30 11:30:05 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		while (haystack[i + j] == needle[j] && needle[j] != '\0'
			&& i + j < len && haystack[i + j] != '\0')
			j++;
		if (needle[j] == '\0')
			return ((char *)&haystack[i]);
		i++;
		j = 0;
	}
	return (NULL);
}

/*int main(void)
{
	const char *haystack = "lorem ipsum dolor sit amet";
	const char *needle = "dolor";
	size_t len = 15;
	char *result = ft_strnstr(haystack, needle, len);
	printf("%s\n", result);
	return 0;
}*/
