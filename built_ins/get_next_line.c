/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleon-la <jleon-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:50:57 by jleon-la          #+#    #+#             */
/*   Updated: 2024/03/04 16:55:05 by jleon-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	get_leftover(char *buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	j = 0;
	if (!buffer[i])
	{
		ft_bzero(&buffer[j], BUFFER_SIZE - j);
		return ;
	}
	while (buffer[i + j])
	{
		buffer[j] = buffer[i + j];
		j++;
	}
	ft_bzero(&buffer[j], BUFFER_SIZE - j);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(sizeof(char) * 1);
	if (!line)
		return (free(line), NULL);
	line[0] = '\0';
	if (ft_strlen(buffer) >= 1)
		line = ft_strjoin(line, buffer);
	while (!ft_strchr(buffer, '\n'))
	{
		ft_bzero(&buffer, BUFFER_SIZE);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(line), NULL);
		if (bytes_read == 0)
			break ;
		line = ft_strjoin(line, buffer);
	}
	if (line[0] == '\0')
		return (free(line), NULL);
	return (get_leftover(buffer), line);
}

// int	main(void)
// {
// 	int	fd;

// 	fd = open("1char.txt", O_RDONLY );
// 	// fd = open("holawenas.txt", O_RDONLY);
// 	//printf("FD=>%d\n", fd);
// 	printf("LINEA1=>%s", get_next_line(fd));
// 	//printf("FD=>%d\n", fd);
// 	printf("LINEA2=>%s", get_next_line(fd));
// 	// printf("FD=>%d", fd);
// 	printf("LINEA3=>%s", get_next_line(fd));
// 	// printf("FD=>%d", fd);
// 	// printf("LINEA4=>%s", get_next_line(fd));
// 	// printf("FD=>%d", fd);
// 	// printf("LINEA5=>%s", get_next_line(fd));
// 	// printf("FD=>%d", fd);
// 	// printf("LINEA6=>%s", get_next_line(fd));
// 	close(fd);
// 	return (0);
// }
