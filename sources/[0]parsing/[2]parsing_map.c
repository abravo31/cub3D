#include "../../includes/cub3D_struct.h"

// static void	ft_print_map(t_map *map)
// {
// 	int	i;
// 	int j;

// 	i = 0;
// 	while (i < map->max_h)
// 	{
// 		j = 0;
// 		while (j < map->max_w)
// 		{
// 			printf("%4d", map->map[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}
// }

void	ft_free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->max_h)
		free(map->map[i++]);
	free(map->map);
	map->map = NULL;
}

/**************************************************************/

static void	ft_scan_around(t_map *map, int y, int x, int error_int)
{
	if ((x < 0 || x == map->max_w) || (y < 0 || y == map->max_h))
		return ;
	if (map->map[y][x] == error_int)
	{
		if (map->valide_map)
			printf(MAP_UNCLOSED);
		map->valide_map = 0;
	}
}

static void	ft_scan_point_area(t_map *map, int y, int x, int empty)
{
	int	error_int;

	if (empty)
		error_int = 0;
	else
		error_int = 32;
	// Top
	ft_scan_around(map, y + 1, x, error_int);
	// Down
	ft_scan_around(map, y - 1, x, error_int);
	// Rigth
	ft_scan_around(map, y, x + 1, error_int);
	// Left
	ft_scan_around(map, y, x - 1, error_int);
}

static int	ft_check_empty_space(t_map *map, int y, int x, int empty)
{
	if (y == 0 || y == (map->max_h - 1))
		return (1);
	else if (x == 0 || x == (map->max_w - 1))
		return (1);
	ft_scan_point_area(map, y, x, empty);
	return (0);
}


static int	ft_check_doors(t_map *map, int y, int x)
{
	if (y == 0 || y == (map->max_h - 1))
		return (1);
	else if (x == 0 || x == (map->max_w - 1))
		return (1);
	if (map->map[y - 1][x] == 1 || map->map[y + 1][x] == 1)
	{
		if ((map->map[y - 1][x] != 1 || map->map[y + 1][x] != 1)
			|| (map->map[y][x - 1] != 0 || map->map[y][x + 1] != 0))
		{
			return (1);
		}
	}
	else if (map->map[y][x - 1] == 1 || map->map[y][x + 1] == 1)
	{
		if ((map->map[y][x - 1] != 1 || map->map[y][x + 1] != 1)
			|| (map->map[y - 1][x] != 0 || map->map[y + 1][x] != 0))
		{
			return (1);
		}
	}
	return (0);
}

static int	ft_scan_map(t_map *map, int i, int j)
{
	while (i < map->max_h)
	{
		j = 0;
		while (j < map->max_w)
		{
			if (ft_check_player(map, map->map[i][j], i, j))
				return (1);
			if (map->map[i][j] == 32)
				ft_scan_point_area(map, i, j, 1);
			else if (map->map[i][j] == 0)
			{
				if (ft_check_empty_space(map, i, j, 0))
					return (printf(MAP_UNCLOSED), 1);
			}
			else if (map->map[i][j] == 2)
			{
				if (ft_check_doors(map, i, j))
					return (printf(INVALID_DOOR_POS), 1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_check_map(t_cub3D *data)
{
	t_map	map;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (ft_get_map(&data->map_list, &map))
		return (1);
	// ft_print_map(&map);
	if (ft_scan_map(&map, i, j))
		return (ft_free_map(&map), 1);
	if (!map.player._is_set)
		return (printf (PLAYER_NONE), ft_free_map(&map), 1);
    // ft_free_map(&map);
	data->map = map;
	return (0);
}
