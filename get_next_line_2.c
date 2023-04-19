#include "get_next_line.h"

size_t ft_strlen(char *str)
{
    int i;
   
    if (!str || !str[0])
        return (0); 
    i = 0;
    while (str[i])
        i++;
    return (i);
}

void *ft_memcpy(void *dest, const void *src, int len)
{
    int i;
    
    i = 0;
    while (src && i < len)
    {
        ((char *)dest)[i] = ((const char *)src)[i];
        i++;
    }
    return (dest);
}

char *new_buf(char *buf, size_t len_read)
{
    int i;
    int len;

    len = ft_strlen(buf + len_read);
    if (len)
        ft_memcpy(buf, buf + len_read, len);
    i = 0;
    while ((i + len) < BUFFER_SIZE && buf[i + len])
    {
        buf[i + len] = '\0';
        i++;
    }
    return (buf);
}

char *copy_new_line(char *line, char *buf)
{
    size_t i;
    size_t len;
    char *stock;
    
    len = ft_strlen(line);
    i = 0;
    while (buf && buf[i] && buf[i] != '\n')
        i++;
    if (buf[i] == '\n')
        i++;
    stock = malloc(sizeof(char) * (len + i + 1));
    if (!stock)
        return (NULL);
    stock[len + i] = '\0';
    ft_memcpy(stock, line, len);
    ft_memcpy(&stock[len], buf, i);
    new_buf(buf, i);
    if (line)
    {
        free(line);
        line = NULL;
    }
    return (stock);
}

size_t is_nline(char *line)
{
    int i;
    if (!line)
        return (0);
    i = 0;
    while (line[i])
    {
        if (line[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

char	  *get_next_line(int fd)
{
    static char buf[BUFFER_SIZE + 1];
    ssize_t count;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    count = 1;
    line = NULL;
    while (!is_nline(line) && count)
    {
      
        if (!buf[0])
        {  
            count = read(fd, buf, BUFFER_SIZE);
            if (count < 0)
                count = 0;
            buf[BUFFER_SIZE] = '\0';
        }
        line = copy_new_line(line, buf);
        if (!line)
            break ;
    }
    if (!line || !line[0])
        return(free(line), NULL);
    return (line);
}

int main ()
{
    char *line;
    int fd;
    
    fd = 0;
    line = get_next_line(fd);
    while(line)
    {
        printf("line : %s", line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (0);
}