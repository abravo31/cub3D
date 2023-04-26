#include "../../includes/cub3D_struct.h"

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

void	data_init(t_cub3D *data)
{
	data->NO = 0;
	data->SE = 0;
	data->WE = 0;
	data->EA = 0;
	data->F = 0;
	data->C = 0;
    data->Y = -1;
	data->ident_coord = NULL;
	data->ident_FC = NULL;
	data->parsing_error = NULL;
    data->map_list = NULL;
}

int main ()
{
    char *line;
    int fd;
	t_cub3D data;
    
	data_init(&data);
    fd = open("test.txt", O_RDONLY);
    line = get_next_line(fd);
    while(line)
    {
		get_list(&data, line);
        free(line);
        line = get_next_line(fd);
    }
    free(line);
	__debug_parsing(&data);
    close(fd);
    ft_exit_and_free(&data, 0, NULL, NULL);
    return (0);
}

// int main(int argc, char *argv[])
// {
// 	(void)argv;
// 	if (argc == 2)
// 		printf("We can lauch the program\n");
// 	else
// 		printf("Invalid number of arguments\n");
// 	return (0);
// }