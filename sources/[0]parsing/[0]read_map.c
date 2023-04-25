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

static int	ft_get_lines_from_file(int fd_map, t_list **lst)
{
	char	*line;
	t_list	*aux;
	char	c;

	line = get_next_line(fd_map);
	if (!line)
		return (1);
	while (line)
	{
		aux = ft_lstnew((void *)line);
		if (!aux)
			return (free(line), 1);
		ft_lstadd_back(lst, aux);
		free(line);
		line = get_next_line(fd_map);
		if (!line && read(fd_map, &c, sizeof(char)) > 0)
			return (generic_lst_free(lst), 1);
	}
	close(fd_map);
	return (0);
}

static int	ft_length_until_new_line(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			break ;
		i++;
	}
	return (i);
}

static int	ft_consider_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0')
			return (1);
		i++;
	}
	return (0);
}

static int	ft_initialize_map(t_list **lst, t_map *map, int begin_idx, int max_width)
{
	// printf("donde comienza %d -- donde termina %d\n", begin_idx, ft_lstsize(*lst));
	map->begin_idx = begin_idx;
	map->max_width = max_width;
	map->max_heigth = ft_lstsize(*lst) - begin_idx;
	// printf("%d\n", map->max_heigth);
	map->closed_map = 1;
	map->map = (int  **)malloc(sizeof(int *) * (map->max_heigth + 1));
	if (!map->map)
		return (1);
	return (0);
}

static int	ft_get_pos_map_in_file(t_list **lst, t_map *map)
{
	t_list	*aux;
	int		b_idx;
	int		i;
	int		max_w;

	max_w = -1;
	aux = *lst;
	i = 0;
	b_idx = -1;
	while (aux)
	{
		// Here we find the index of the first line of the map in the file
		if (ft_consider_line((char *)aux->content) && b_idx == -1)
			b_idx = i;
		if (!ft_consider_line((char *)aux->content) && b_idx != -1)
		{
			while (aux)
			{
				if (ft_consider_line((char *)aux->content))
					return (printf(MAP_IS_NOT_LAST_ELEM), 1);
				if (ft_length_until_new_line((char *)aux->content) > max_w)
					max_w = ft_length_until_new_line((char *)aux->content);
				aux = aux->next;
			}
			// Ce break sert à qqc ?
			break ;
		}
		if (b_idx != -1)
		{
			if (ft_length_until_new_line((char *)aux->content) > max_w)
				max_w = ft_length_until_new_line((char *)aux->content);
		}
		i++;
		aux = aux->next;
	}
	if (ft_initialize_map(lst, map, b_idx, max_w))
		return (1);
	return (0);
}

static void ft_create_tab_from_line(int *map_l, char *l, int max_w, int full)
{
	int	i;

	i = 0;
	while (l[i])
	{
		if ((int)l[i] == 10)
			break ;
		else if ((int)l[i] == 48 || (int)l[i] == 49)
			map_l[i] = (int)l[i] - '0';
		else
			map_l[i] = (int)l[i];
		i++;
	}
	if (full != 1)
	{
		while (i < (max_w))
		{
			map_l[i] = 32;
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
	while (i++ < map->begin_idx)
		aux = aux->next;
	while (aux)
	{
		line = (char *)aux->content;
		map->map[i - map->begin_idx - 1] = (int *)malloc(sizeof(int) * map->max_width);
		if (!map->map[i - map->begin_idx - 1])
			return (ft_free_map(map), 1);
		if (ft_length_until_new_line(line) < map->max_width)
			ft_create_tab_from_line(map->map[i - map->begin_idx - 1], line, map->max_width, 0);
		else
			ft_create_tab_from_line(map->map[i - map->begin_idx - 1], line, map->max_width, 1);
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
	if (ft_get_pos_map_in_file(begin_lines_map, map))
		return (generic_lst_free(begin_lines_map), 1);
	if (ft_create_map_from_list(begin_lines_map, map))
		return (generic_lst_free(begin_lines_map), 1);
	generic_lst_free(begin_lines_map);
	close (fd_map);
	return (0);
}

