#include "get_next_line_bonus.h"

size_t  ft_strlen(const char *s)
{
    size_t i = 0;
    while (s && s[i])
        i++;
    return i;
}

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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*ptr;
	size_t	size1;
	size_t	size2;

	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (size1 + size2 + 1));
	ptr = str;
	if (!str)
		return (0);
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
    *str = '\0';
	return (ptr);
}

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
