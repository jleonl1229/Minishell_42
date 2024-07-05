/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleon-la <jleon-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:50:24 by jleon-la          #+#    #+#             */
/*   Updated: 2024/03/04 20:12:24 by jleon-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h" 

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	while (s[l])
	{
		l++;
	}
	while (i <= l)
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	return (NULL);
}

size_t	ft_strlen(const char *length)
{
	int	i;

	i = 0;
	while (length[i] && length[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*memory;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if ((!s1 || s1 == NULL) || (!s2 || s2 == NULL))
		return (NULL);
	memory = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!memory)
		return (NULL);
	while (s1[i] && s1[i] != '\0')
	{
		memory[i] = s1[i];
		i++;
	}
	while (s2[j] && s2[j] != '\0' && s2[j] != '\n')
		memory[i++] = s2[j++];
	if (s2[j] == '\n')
		memory[i++] = s2[j++];
	memory[i] = '\0';
	free(s1);
	return (memory);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dst == 0 && src == 0)
	{
		return (dst);
	}
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}
