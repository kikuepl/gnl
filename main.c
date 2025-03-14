#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
    int fd;
    char *line;

    // コマンドライン引数がなければ標準入力から読み込む
    if (argc < 2)
    {
        fd = 0; // 標準入力 (stdin)
        printf("Reading from standard input. Enter text (Ctrl+D to end):\n");
    }
    else
    {
        fd = open(argv[1], O_RDONLY);
        if (fd < 0)
        {
            perror("Error opening file");
            return 1;
        }
    }

    // get_next_line() を使って1行ずつ読み込む
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    if (argc >= 2)
        close(fd);

    return 0;
}
