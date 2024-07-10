/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:27:48 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/06/26 10:46:56 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_substrings(const char *s, char c)
{
	size_t	count;
	int		in_substring;

	count = 0;
	in_substring = 0;
	while (*s != '\0')
	{
		if (*s == c)
			in_substring = 0;
		else
		{
			if (in_substring == 0)
			{
				in_substring = 1;
				count++;
			}
		}
		s++;
	}
	return (count);
}

static size_t	ft_count_char(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (s[count] != c && s[count] != '\0')
		count++;
	return (count);
}

static char	**ft_free(char **pointer, size_t substrings)
{
	size_t	i;

	i = 0;
	while (i < substrings)
	{
		free(pointer[i]);
		++i;
	}
	free(pointer);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**pointer;
	size_t	substrings;
	size_t	i;
	size_t	substr_length;

	i = 0;
	substr_length = 0;
	substrings = ft_count_substrings(s, c);
	pointer = malloc(sizeof(char *) * (substrings + 1));
	if (pointer == NULL)
		return (NULL);
	while (i < substrings)
	{
		while (*s == c)
			s++;
		substr_length = ft_count_char(s, c);
		pointer[i] = malloc(sizeof(char) * (substr_length + 1));
		if (pointer[i] == NULL)
			return (ft_free(pointer, i));
		ft_strlcpy(pointer[i], s, substr_length + 1);
		s += substr_length;
		i++;
	}
	pointer[i] = NULL;
	return (pointer);
}
/*int main(void)
{
    char const  *s = "xxxxxxxxxhello!";
    char c = 'x';
    int i = 0;
    char    **result = ft_split(s,c);
    while (result[i] != NULL)
    {
        printf("%s\n", result[i]);
        i++;
    }
}*/
