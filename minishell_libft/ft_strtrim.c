/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:12:51 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/01/30 11:31:08 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	begin;
	size_t	end;
	char	*trim;

	begin = 0;
	end = ft_strlen(s1);
	while (begin < end && ft_strchr(set, s1[begin]) != NULL)
		begin++;
	if (begin == end)
		return (ft_strdup(""));
	end--;
	while (end != 0 && ft_strchr(set, s1[end]) != NULL)
		end--;
	trim = malloc(end - begin +2);
	if (trim != NULL)
	{
		ft_strlcpy(trim, &s1[begin], end - begin + 2);
		return (trim);
	}
	return (NULL);
}

/*int main(void)
{
    char const *s1 = "aaa";
    char const *set = "a";
    char *result = ft_strtrim(s1,set);
    printf("%s\n", result);
    return (0);
}*/
