#include "get_next_line.h"

// 文字列の長さを返す関数
size_t  ft_strlen(const char *s)
{
    size_t i = 0;
    while (s && s[i])
        i++;
    return i;
}

// 文字列内に特定の文字 c があるか探す関数
char    *ft_strchr(const char *s, int c)
{
    if (!s)
        return NULL;
    while (*s)
    {
        if (*s == (char)c)
            return (char *)s;
        s++;
    }
    if ((char)c == '\0')
        return (char *)s;
    return NULL;
}

// 2つの文字列を連結して新しい文字列を返す関数
char    *ft_strjoin(char const *s1, char const *s2)
{
    char    *joined;
    size_t  i = 0, j = 0;
    size_t  len1 = ft_strlen(s1);
    size_t  len2 = ft_strlen(s2);

    joined = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
    if (!joined)
        return NULL;
    while (s1 && s1[i])
    {
        joined[i] = s1[i];
        i++;
    }
    while (s2 && s2[j])
    {
        joined[i + j] = s2[j];
        j++;
    }
    joined[i + j] = '\0';
    return joined;
}

// 文字列を複製する関数
char    *ft_strdup(const char *s1)
{
    size_t  len = ft_strlen(s1);
    char    *dup = malloc(sizeof(char) * (len + 1));
    size_t  i = 0;
    if (!dup)
        return NULL;
    while (i < len)
    {
        dup[i] = s1[i];
        i++;
    }
    dup[i] = '\0';
    return dup;
}
