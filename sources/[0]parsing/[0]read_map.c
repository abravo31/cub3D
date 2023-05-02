#include "../../includes/cub3D_struct.h"

void print_data_lst(t_list **begin_lst)
{
	t_list          *aux;
	t_map_list		*aux_map_line;
	
	aux = *begin_lst;
	while (aux)
	{
		aux_map_line = (t_map_list *)aux->content;
		printf("line %d\n", aux_map_line->_y);
		printf("line %d\n", aux_map_line->_x);
		printf("line %s\n", aux_map_line->line);
		aux = aux->next;
	}
}
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

// static int	ft_get_lines_from_file(int fd_map, t_list **lst)
// {
// 	char	*line;
// 	t_list	*aux;
// 	char	c;

// 	line = get_next_line(fd_map);
// 	if (!line)
// 		return (1);
// 	while (line)
// 	{
// 		aux = ft_lstnew((void *)line);
// 		if (!aux)
// 		{
// 			printf("Malloc failed\n");
// 			generic_lst_free(lst);
// 			return (free(line), 1);
// 		}
// 		ft_lstadd_back(lst, aux);
// 		free(line);
// 		line = get_next_line(fd_map);
// 		if (!line && read(fd_map, &c, sizeof(char)) > 0)
// 			return (generic_lst_free(lst), 1);
// 	}
// 	close(fd_map);
// 	return (0);
// }

int	ft_length_until_new_line(char *s)
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
	int	flag_not_char_map;

	flag_not_char_map = 0;
	i = 0;
	// printf("line : %s\n", line);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
		{
			if (flag_not_char_map != 1)
				flag_not_char_map  = 1;
			if (!(line[i] >= '0' && line[i] <= '2') && !(line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W'))
			{
				flag_not_char_map = 2;
			}
		}
		i++;
	}
	if (!flag_not_char_map)
		return (1);
	return (0);
}

static int	ft_initialize_map(t_list **lst, t_map *map)
{
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

/*
Here we find the index (in the linked list) of the first line of
the map in the file checking (using ft_consider_line function) if in
the line contains at least one '0', '1', 'W', 'S', 'E', 'W'
*/
static int	ft_scan_line(t_list **lst, t_map *map, int *i)
{
	t_list	*aux;
	int		is_valid_line;

	aux = generic_get_node_by_idx(lst, *i);
	is_valid_line = ft_consider_line(((t_map_list *)(aux->content))->line);
	if (is_valid_line && map->b_idx == -1)
	{
		printf("Begin in index: %d\n", *i);
		map->b_idx = *i;
	}
	else if (is_valid_line && map->b_idx != -1)
	{
		if (!ft_consider_line(((t_map_list *)(aux->content))->line) && map->b_idx != -1)
		{
			if (map->l_idx == -1)
				map->l_idx = *i;
			while (aux)
			{
				if (ft_consider_line(((t_map_list *)(aux->content))->line))
					return (printf(MAP_IS_NOT_LAST_ELEM), 1);
				if (ft_length_until_new_line(((t_map_list *)(aux->content))->line) > map->max_w)
					map->max_w = ft_length_until_new_line(((t_map_list *)(aux->content))->line);
				aux = aux->next;
			}
		}
	}
	// if (!ft_consider_line(((t_map_list *)(aux->content))->line) && map->b_idx != -1)
	// {
	// 	if (map->l_idx == -1)
	// 		map->l_idx = *i;
	// 	while (aux)
	// 	{
	// 		if (ft_consider_line(((t_map_list *)(aux->content))->line))
	// 			return (printf(MAP_IS_NOT_LAST_ELEM), 1);
	// 		if (ft_length_until_new_line(((t_map_list *)(aux->content))->line) > map->max_w)
	// 			map->max_w = ft_length_until_new_line(((t_map_list *)(aux->content))->line);
	// 		aux = aux->next;
	// 	}
	// }
	return (0);
	// if (ft_consider_line(((t_map_list *)(aux->content))->line) && map->b_idx == -1)
	// 	map->b_idx = *i;
	// if (!ft_consider_line(((t_map_list *)(aux->content))->line) && map->b_idx != -1)
	// {
	// 	if (map->l_idx == -1)
	// 		map->l_idx = *i;
	// 	while (aux)
	// 	{
	// 		if (ft_consider_line(((t_map_list *)(aux->content))->line))
	// 			return (printf(MAP_IS_NOT_LAST_ELEM), 1);
	// 		if (ft_length_until_new_line(((t_map_list *)(aux->content))->line) > map->max_w)
	// 			map->max_w = ft_length_until_new_line(((t_map_list *)(aux->content))->line);
	// 		aux = aux->next;
	// 	}
	// }
	// return (0);
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
			if (((t_map_list *)(aux->content))->_x > map->max_w)
				map->max_w = ((t_map_list *)(aux->content))->_x;
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
		else if ((int)l[i] >= 48 && (int)l[i] <= 50)
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
		line = ((t_map_list *)(aux->content))->line;
		map->map[i - map->b_idx - 1] = (int *)malloc(sizeof(int) * map->max_w);
		if (!map->map[i - map->b_idx - 1])
			return (ft_free_map(map), 1);
		if (((t_map_list *)(aux->content))->_x < map->max_w)
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

int	ft_read_file(t_list **lst, t_map *map)
{
	print_data_lst(lst);
	if (ft_get_pos_map_in_file(lst, map))
		return (1);
	if (ft_create_map_from_list(lst, map))
		return (1);
	// generic_lst_free(lst);
	return (0);
}

