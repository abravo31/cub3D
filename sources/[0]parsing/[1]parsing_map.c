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
		map->closed_map = 0;
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

void	ft_scan_map(t_map *map)
{
	int	i;
	int j;

	i = 0;
	while (i < map->max_h)
	{
		j = 0;
		while (j < map->max_w)
		{
			if (map->map[i][j] == 32)
				ft_scan_point_area(map, i, j, 1);
			else if (map->map[i][j] == 0)
				ft_scan_point_area(map, i, j, 0);

			j++;
		}
		i++;
	}
}

int	ft_check_map(char *file_name)
{
	t_map	map;

	if (ft_read_file(file_name, &map))
		return (1);
	ft_print_map(&map);
	ft_scan_map(&map);
	if (map.closed_map == 0)
	{
		ft_free_map(&map);
		return (printf(INVALID_MAP), 1);
	}
	else
	{
		printf("Valido\n");
	}
    ft_free_map(&map);
	return (0);
}
