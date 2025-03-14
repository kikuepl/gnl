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

// 残りの文字列から 1 行分を抽出し、残りを更新する補助関数
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
        // 改行文字までの長さを計算（改行文字も含む）
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
        // 残りの部分を更新
        temp = ft_strdup(*rest + line_length);
        free(*rest);
        *rest = temp;
        // 残りの文字列が空の場合は NULL にする
        if (**rest == '\0')
        {
            free(*rest);
            *rest = NULL;
        }
    }
    else
    {
        // 改行が見つからない場合は、残り全体を返す
        line = ft_strdup(*rest);
        free(*rest);
        *rest = NULL;
    }
    return line;
}

char    *get_next_line(int fd)
{
    static char *rest;
    char        buffer[BUFFER_SIZE + 1];
    ssize_t     bytes_read;
    char        *temp;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    // 改行が見つかるまでループする
    while (!ft_strchr(rest, '\n'))
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read < 0)
        {
            if (rest)
            {
                free(rest);
                rest = NULL;
            }
            return NULL;
        }
        if (bytes_read == 0)
            break;
        buffer[bytes_read] = '\0';
        if (!rest)
            rest = ft_strdup(buffer);
        else
        {
            temp = ft_strjoin(rest, buffer);
            free(rest);
            rest = temp;
        }
    }
    return get_line(&rest);
}
