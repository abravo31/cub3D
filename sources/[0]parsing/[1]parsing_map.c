#include "../../includes/cub3D_struct.h"

static void	ft_print_map(t_map *map)
{
	int	i;
	int j;

	i = 0;
	while (i < map->max_h)
	{
		j = 0;
		while (j < map->max_w)
		{
			printf("%4d", map->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

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
		map->valide_map = 0;
		if (error_int == 32)
			printf(MAP_UNCLOSED);
		else
			printf(INVALID_MAP);
	}
}

void	ft_scan_point_area(t_map *map, int y, int x, int empty)
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

static int	ft_check_player(t_map *map, int c_player, int y, int x)
{
	if (c_player == 'N' || c_player == 'S' || c_player == 'E' || c_player == 'W')
	{
		if (!map->player._is_set)
		{
			map->player._direction = 0;
			map->player._y = y;
			map->player._x = x;
			map->player._is_set = 1;
		}
		else
			return (1);
	}
	return (0);
}

int	ft_scan_map(t_map *map)
{
	int	i;
	int j;

	i = 0;
	while (i < map->max_h)
	{
		j = 0;
		while (j < map->max_w)
		{
			if (ft_check_player(map, map->map[i][j], i, j))
				return (printf(DOUBLE_PLAYER), 1);
			if (map->map[i][j] == 32)
				ft_scan_point_area(map, i, j, 1);
			else if (map->map[i][j] == 0)
				ft_scan_point_area(map, i, j, 0);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_check_map(char *file_name)
{
	t_map	map;

	if (ft_read_file(file_name, &map))
		return (1);
	if (ft_scan_map(&map))
		return (ft_free_map(&map), 1);
	if (map.valide_map == 0)
	{
		ft_free_map(&map);
		return (printf(INVALID_MAP), 1);
	}
	ft_print_map(&map);
    ft_free_map(&map);
	return (0);
}
