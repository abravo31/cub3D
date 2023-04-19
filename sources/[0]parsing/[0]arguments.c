#include "../../includes/cub3D_struct.h"

static int	ft_get_lines_from_file(char *file_name, t_list **lst)
{
	int		fd_map;
	char	*line;
	t_list	*aux;
	char	c;

	fd_map = open(file_name, O_RDONLY);
	if (fd_map == -1)
		return (1);
	line = get_next_line(fd_map);
	while (line)
	{
		aux = ft_lstnew((void *)line);
		if (!aux)
		{
			free(line);
			return (1);
		}
		ft_lstadd_back(lst, aux);
		free(line);
		line = get_next_line(fd_map);
		if (!line && read(fd_map, &c, sizeof(char)) > 0)
			return (ft_free_list(*lst));
	}
	close(fd_map);
	return (0);
}

static int	ft_number_words_in_line(char *str, char sep)
{
	int		i;
	int		number_words;
	char	*str_trim;

	str_trim = ft_strtrim(str, " \n");
	number_words = 0;
	i = 0;
	while (str_trim[i])
	{
		while (str_trim[i] && str_trim[i] == sep)
			i++;
		if (str_trim[i] && str_trim[i] != sep)
		{
			number_words++;
			while (str_trim[i] && str_trim[i] != sep)
				i++;
		}
	}
	free (str_trim);
	return (number_words);
}

/*Setting map->is_rectancle_map*/
static int	ft_get_dimensions_map(t_list *lst, t_map *map)
{
	char	*line;
	t_list	*aux;

	aux = lst;
	while (aux)
	{
		line = (char *)aux->content;
		if (map->map_width == 0)
			map->map_width = ft_number_words_in_line(line, ' ');
		else if (map->map_width != ft_number_words_in_line(line, ' '))
		{
			ft_free_list(lst);
			return (1);
		}
		map->map_heigth++;
		aux = aux->next;
	}
	map->amount_vec = map->map_width * map->map_heigth;
	ft_free_list(lst);
	return (0);
}

int	ft_read_file(char *file_name, t_lstb **lst_tabs, t_map *map)
{
	t_list		*lines_map;

	lines_map = NULL;
	if (ft_get_lines_from_file(file_name, &lines_map))
		return (1);
	
	if (ft_get_dimensions_map(lines_map, map) || (map->amount_vec == 0))
		return (1);
	return (0);
}

