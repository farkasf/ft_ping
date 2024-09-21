/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffarkas <ffarkas@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 02:30:41 by ffarkas           #+#    #+#             */
/*   Updated: 2023/02/03 05:32:40 by ffarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_next(char *buffer)
{
	char	*next_line;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == 0)
	{
		free(buffer);
		return (NULL);
	}
	next_line = (char *)malloc((ft_strlen(buffer) - i + 1) * sizeof(char));
	if (next_line == 0)
		return (0);
	i++;
	j = 0;
	while (buffer[i])
		next_line[j++] = buffer[i++];
	next_line[j] = '\0';
	free(buffer);
	return (next_line);
}

char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (buffer[i] == 0)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = (char *)malloc((i + 2) * sizeof(char));
	if (line == 0)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_read(int fd, char *buffer)
{
	char	*read_buffer;
	int		bytes_read;

	read_buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (read_buffer == 0)
		return (NULL);
	bytes_read = 1;
	while (bytes_read != 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(read_buffer);
			return (NULL);
		}
		read_buffer[bytes_read] = '\0';
		buffer = ft_strjoin_gnl(buffer, read_buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free (read_buffer);
	return (buffer);
}

char	*ft_get_next_line(int fd)
{
	static char	*buffer[2048];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = ft_read(fd, buffer[fd]);
	if (buffer[fd] == 0)
		return (NULL);
	line = ft_line(buffer[fd]);
	buffer[fd] = ft_next(buffer[fd]);
	return (line);
}
