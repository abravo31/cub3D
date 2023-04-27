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

t_list	*generic_get_node_by_idx(t_list **lst, int idx)
{
	t_list	*lst_ptr;
	int		i;

	if (lst)
	{
		lst_ptr = *lst;
		i = 0;
		while (i < idx)
		{
			i++;
			lst_ptr = lst_ptr->next;
		}
		return (lst_ptr);
	}
	return (NULL);
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
		{
			printf("Malloc failed\n");
			generic_lst_free(lst);
			return (free(line), 1);
		}
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
		if (line[i] == '1' || line[i] == '0' || line[i] == 'N' ||
			line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			return (1);
		// else if (line[i] == '\n' || line[i] == '\t' || line[i] == ' ')
		// 	return (2);
		i++;
	}
	return (0);
}

static int	ft_initialize_map(t_list **lst, t_map *map)
{
	// printf("%d --- %d\n", map->b_idx, map->l_idx);
	if (map->l_idx == -1)
		map->max_h = ft_lstsize(*lst) - map->b_idx;
	else
		map->max_h = map->l_idx - map->b_idx;
	map->valide_map = 1;
	map->player._is_set = 0;
	map->map = (int  **)malloc(sizeof(int *) * (map->max_h + 1));
	if (!map->map)
		return (1);
	return (0);
}

static int	ft_scan_line(t_list **lst, t_map *map, int *i)
{
	t_list	*aux;

	aux = generic_get_node_by_idx(lst, *i);
	/*
	Here we find the index (in the linked list) of the first line of
	the map in the file checking (using ft_consider_line function) if in
	the line contains at least one '0', '1', 'W', 'S', 'E', 'W'
	*/
	if (ft_consider_line((char *)aux->content) && map->b_idx == -1)
		map->b_idx = *i;
	if (!ft_consider_line((char *)aux->content) && map->b_idx != -1)
	{
		if (map->l_idx == -1)
			map->l_idx = *i;
		while (aux)
		{
			if (ft_consider_line((char *)aux->content))
				return (printf(MAP_IS_NOT_LAST_ELEM), 1);
			if (ft_length_until_new_line((char *)aux->content) > map->max_w)
				map->max_w = ft_length_until_new_line((char *)aux->content);
			aux = aux->next;
		}
	}
	return (0);
}

static int	ft_get_pos_map_in_file(t_list **lst, t_map *map)
{
	t_list	*aux;
	int		i;

	aux = *lst;
	map->b_idx = -1;
	map->max_w = -1;
	map->l_idx = -1;
	i = 0;
	while (aux)
	{
		if (ft_scan_line(lst, map, &i))
			return (1);
		if (map->b_idx != -1)
		{
			if (ft_length_until_new_line((char *)aux->content) > map->max_w)
				map->max_w = ft_length_until_new_line((char *)aux->content);
		}
		i++;
		aux = aux->next;
	}
	if (ft_initialize_map(lst, map))
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
	while (i++ < map->b_idx)
		aux = aux->next;
	while (aux)
	{
		line = (char *)aux->content;
		map->map[i - map->b_idx - 1] = (int *)malloc(sizeof(int) * map->max_w);
		if (!map->map[i - map->b_idx - 1])
			return (ft_free_map(map), 1);
		if (ft_length_until_new_line(line) < map->max_w)
			ft_create_tab_from_line(map->map[i - map->b_idx - 1], line, map->max_w, 0);
		else
			ft_create_tab_from_line(map->map[i - map->b_idx - 1], line, map->max_w, 1);
		if (i == map->l_idx)
			break ;
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
		return (close(fd_map), 1);
	close(fd_map);
	if (ft_get_pos_map_in_file(begin_lines_map, map))
		return (generic_lst_free(begin_lines_map), 1);
	if (ft_create_map_from_list(begin_lines_map, map))
		return (generic_lst_free(begin_lines_map), 1);
	generic_lst_free(begin_lines_map);
	return (0);
}

