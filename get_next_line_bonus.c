/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sytorium <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:04:20 by sytorium          #+#    #+#             */
/*   Updated: 2025/03/25 13:37:40 by sytorium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

char	*extract_line(char **rest, char *ptr)
{
	size_t	line_length;
	char	*temp_line;
	char	*line;	

	line_length = ptr - *rest + 1;
	line = ft_substr(*rest, 0, line_length);
	if (line == NULL)
		return (NULL);
	temp_line = ft_strdup(*rest + line_length);
	if (temp_line == NULL)
	{
		free(line);
		return (NULL);
	}
	free(*rest);
	*rest = temp_line;
	if (**rest == '\0')
	{
		free(*rest);
		*rest = NULL;
	}
	return (line);
}

static char	*get_line(char **rest)
{
	char	*line;
	char	*newline_ptr;

	if (!*rest)
		return (NULL);
	newline_ptr = ft_strchr(*rest, '\n');
	if (newline_ptr)
	{
		line = extract_line(rest, newline_ptr);
	}
	else
	{
		line = ft_strdup(*rest);
		free(*rest);
		*rest = NULL;
	}
	return (line);
}

int	update_rest_buffer(char **rest, char *buffer, ssize_t bytes_read)
{
	char	*temp_line;

	if (bytes_read < 0)
	{
		if (*rest)
		{
			free(*rest);
			*rest = NULL;
		}
		free(buffer);
		return (0);
	}
	if (bytes_read == 0)
		return (1);
	buffer[bytes_read] = '\0';
	if (!*rest)
		*rest = ft_strdup(buffer);
	else
	{
		temp_line = ft_strjoin(*rest, buffer);
		free(*rest);
		*rest = temp_line;
	}
	return (2);
}

char	*get_next_line(int fd)
{
	static char	*rest[FD_MAX];
	char		*buffer;
	int			res;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (rest[fd] == NULL || !ft_strchr(rest[fd], '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		res = update_rest_buffer(&rest[fd], buffer, bytes_read);
		if (res == 0)
			return (NULL);
		if (res == 1)
			break ;
	}
	free(buffer);
	return (get_line(&rest[fd]));
}
