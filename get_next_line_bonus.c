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
#include "get_next_line_bonus.h"

#include "get_next_line_bonus.h"

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
    
    static char *rest[FD_MAX];  //読み取るファイルの残り
    char        *buffer;        //読み取ったデータを格納
    ssize_t     bytes_read;     //読み取ったバイト数
    char        *temp;          //一時的な文字列

    //error処理
    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    //ヒープ領域にBUFFER_SIZE + 1分のメモリを確保
    buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return NULL;
    //rest[fd]がNULLか、改行がない場合
    //全部読み終わった場合か、改行がない場合
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
