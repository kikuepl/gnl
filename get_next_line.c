/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sytorium <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:04:20 by sytorium          #+#    #+#             */
/*   Updated: 2025/03/14 18:04:21 by sytorium         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static char *get_line(char **rest)
{
    char    *line;
    char    *temp;
    char    *newline_ptr;
    size_t  line_length;
    size_t  i;

    if (!*rest)
        return NULL;
    newline_ptr = ft_strchr(*rest, '\n');
    if (newline_ptr)
    {
        line_length = newline_ptr - *rest + 1;
        line = (char *)malloc(sizeof(char) * (line_length + 1));
        if (!line)
            return NULL;
        i = 0;
        while (i < line_length)
        {
            line[i] = (*rest)[i];
            i++;
        }
        line[i] = '\0';
        temp = ft_strdup(*rest + line_length);
        free(*rest);
        *rest = temp;
        if (**rest == '\0')
        {
            free(*rest);
            *rest = NULL;
        }
    }
    else
    {
        line = ft_strdup(*rest);
        free(*rest);
        *rest = NULL;
    }
    return line;
}

char *get_next_line(int fd)
{
    static char *rest[FD_MAX];
    char        *buffer;
    ssize_t     bytes_read;
    char        *temp;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return NULL;
    while (rest[fd] == NULL || !ft_strchr(rest[fd], '\n'))
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read < 0)
        {
            if (rest[fd])
            {
                free(rest[fd]);
                rest[fd] = NULL;
            }
            free(buffer);
            return NULL;
        }
        if (bytes_read == 0)
            break;
        buffer[bytes_read] = '\0';
        if (!rest[fd])
            rest[fd] = ft_strdup(buffer);
        else
        {
            temp = ft_strjoin(rest[fd], buffer);
            free(rest[fd]);
            rest[fd] = temp;
        }
    }
    free(buffer);
    return get_line(&rest[fd]);
}
