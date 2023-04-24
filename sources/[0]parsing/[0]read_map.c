#include "../../includes/cub3D_struct.h"

void	generic_lst_free(t_list **lst)
{
	t_list	*lst_ptr;
	t_list	*aux_lst;

	lst_ptr = *lst;
	if (lst_ptr)
	{
		while (lst_ptr)
		{
			aux_lst = lst_ptr;
			lst_ptr = lst_ptr->next;
			free(aux_lst->content);
			free(aux_lst);
		}
		lst_ptr = NULL;
		*lst = lst_ptr;
	}
}

static int	ft_length_until_new_line(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] || s[i] == '\n')
		i++;
	return (i);
}

static int	ft_get_lines_from_file(int fd_map, t_list **lst)
{
	char	*line;
	t_list	*aux;
	char	c;

	line = get_next_line(fd_map);
	while (line)
	{
		if (ft_strcmp(line, "\n") != 0)
		{
			aux = ft_lstnew((void *)line);
			if (!aux)
				return (free(line), 1);
			ft_lstadd_back(lst, aux);
		}
		free(line);
		line = get_next_line(fd_map);
		if (!line && read(fd_map, &c, sizeof(char)) > 0)
			return (generic_lst_free(lst), 1);
	}
	close(fd_map);
	return (0);
}

static int	ft_initialize_map(t_map *map, int max_width, int max_heigth)
{
	map->max_width = max_width;
	map->max_heigth = max_heigth;
	map->map = (int  **)malloc(sizeof(int *) * (max_heigth + 1));
	if (!map->map)
		return (1);
	return (0);
}

static int	ft_get_dimensions_map(t_list **lst, t_map *map)
{
	t_list	*aux;
	char	*line;
	int		max_width;
	int		max_heigth;

	max_width = 0;
	max_heigth = 0;
	aux = *lst;
	while (aux)
	{
		line = (char *)aux->content;
		if (ft_length_until_new_line(line) > max_width)
			max_width = ft_length_until_new_line(line);
		aux = aux->next;
		if (ft_strcmp(line, "\n") != 0)
			max_heigth++;
	}
	if (ft_initialize_map(map, max_width, max_heigth))
		return (generic_lst_free(lst), 1);
	return (0);
}

static void ft_create_tab_from_line(int *map_l, char *l, int max_w, int full)
{
	int	i;

	i = 0;
	while (l[i])
	{
		if ((int)l[i] == 10)
			map_l[i] = (int)' ';
		else
			map_l[i] = (int)l[i];
		i++;
	}
	if (full != 1)
	{
		while (i < (max_w))
		{
			map_l[i] = (int)' ';
			i++;
		}
	}
}

static int	ft_create_map_from_list(t_list **lst, t_map *map)
{
	t_list	*aux;
	char	*line;
	int		i;

	aux = *lst;
	i = 0;
	while (aux)
	{
		line = (char *)aux->content;
		map->map[i] = (int *)malloc(sizeof(int) * map->max_width);
		if (!map->map[i])
			return (ft_free_map(map), 1);
		if (ft_strlen_int(line) < map->max_width)
			ft_create_tab_from_line(map->map[i], line, map->max_width, 0);
		else
			ft_create_tab_from_line(map->map[i], line, map->max_width, 1);
		aux = aux->next;
		i++;
	}
	return (0);
}

int	ft_read_file(char *file_name, t_map *map)
{
	t_list		**begin_lines_map;
	t_list		*lines_map;
	int			fd_map;

	fd_map = open(file_name, O_RDONLY);
	if (fd_map == -1)
		return (printf(ERROR_OPEN_FD), 1);
	lines_map = NULL;
	begin_lines_map = &lines_map;
	if (ft_get_lines_from_file(fd_map, begin_lines_map))
		return (1);
	if (ft_get_dimensions_map(begin_lines_map, map))
		return (1);
	if (ft_create_map_from_list(begin_lines_map, map))
		return (generic_lst_free(begin_lines_map), 1);
	generic_lst_free(begin_lines_map);
	close (fd_map);
	return (0);
}

