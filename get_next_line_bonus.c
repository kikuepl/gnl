#include "get_next_line_bonus.h"

// 指定されたファイルディスクリプタに対応する残りのバッファから
// 1行分を抽出し、残りの部分を更新するヘルパー関数
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
        // 改行文字までの長さ（改行文字も含む）
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

char *get_next_line(int fd)
{
    static char *rest[FD_MAX]; 
    char        buffer[BUFFER_SIZE + 1];
    ssize_t     bytes_read;
    char        *temp;

    if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
        return NULL;
    // 改行が見つかるまでバッファから読み込む
    while (!ft_strchr(rest[fd], '\n'))
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read < 0)
        {
            if (rest[fd])
            {
                free(rest[fd]);
                rest[fd] = NULL;
            }
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
    return get_line(&rest[fd]);
}
