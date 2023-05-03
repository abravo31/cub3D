#include "../../includes/cub3D_struct.h"

char	*new_buf(char *buf, size_t len_read)
{
	int	i;
	int	len;

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

char	*copy_new_line(char *line, char *buf)
{
	size_t	i;
	size_t	len;
	char	*stock;

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

size_t	is_nline(char *line)
{
	int	i;

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

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	ssize_t		count;
	char		*line;

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
		return (free(line), NULL);
	return (line);
}

void	data_init(t_cub3D *data)
{
	data->no = 0;
	data->so = 0;
	data->we = 0;
	data->ea = 0;
	data->f = 0;
	data->c = 0;
	data->y = -1;
	data->ident_coord = NULL;
	data->ident_fc = NULL;
	data->map_list = NULL;
}

int	gnl_loop(t_cub3D *data, char *file_name)
{
	char	*line;
	int		fd;

	data_init(data);
	fd = open(file_name, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		return (ft_putstr_fd("Failed to open file!\n", 1), 1);
	while (line)
	{
		get_list(data, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (check_full_identifier(data) < 6)
		ft_exit_and_free(data, 1, NULL, IDENT_MISSING);
	// __debug_parsing(data);
	close(fd);
	// Ce ligne la 
	ft_check_map(data);
	// ft_exit_and_free(data, 0, NULL, NULL);
	return (0);
}

static int	ft_check_file_str(char *f_name)
{
	int	idx;
	int	length_f_name;

	length_f_name = ft_strlen_int(f_name);
	idx = ft_idx_last_occur_char(f_name, '/');
	if (idx >= 0 && f_name[idx] == '/' && (idx == (length_f_name - 1)))
		return (printf(ARG_IS_DIR), 1);
	idx = ft_idx_last_occur_char(f_name, '.');
	if (idx < 0 || ft_strncmp(f_name + idx, ".cub", ft_strlen_int(f_name + idx)))
		return (printf(INVALID_EXTENSION), 1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_cub3D	data;

	if (argc == 2)
	{
		if (ft_check_file_str(argv[1]))
			return (1);
		if (gnl_loop(&data, argv[1]))
			return (1);
		if (data.map_list)
			ft_lstclear(&data.map_list, &ft_free_map_list);
		// open_window(&data);
	}
	else
		return (printf("Invalid number of arguments\n"), 1);
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