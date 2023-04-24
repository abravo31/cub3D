#include "../../includes/cub3D_struct.h"

static void	ft_print_map(t_map *map)
{
	int	i;
	int j;

	i = 0;
	while (i < map->max_heigth)
	{
		j = 0;
		while (j < map->max_width)
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
	while (i < map->max_heigth)
		free(map->map[i++]);
	free(map->map);
	map->map = NULL;
}

/**************************************************************/

void	ft_print_around(t_map *map, int y, int x)
{
	if ((x < 0 || x == map->max_width) || (y < 0 || y == map->max_heigth))
		return ;
	// printf("%d\n", map->map[y][x]);
	if (map->map[y][x] == 0)
	{
		map->closed_map = 0;
	}
}

void	ft_scan_point_area(t_map *map, int y, int x)
{
	// printf("Abajo : ");
	ft_print_around(map, y + 1, x);
	// printf("Arriba:	  ");
	ft_print_around(map, y - 1, x);
	// printf("Derecha:  ");
	ft_print_around(map, y, x + 1);
	// printf("Izquierda:");
	ft_print_around(map, y, x - 1);
}

void	ft_scan_map(t_map *map)
{
	int	i;
	int j;

	i = 0;
	while (i < map->max_heigth)
	{
		j = 0;
		while (j < map->max_width)
		{
			if (map->map[i][j] == 32)
				ft_scan_point_area(map, i, j);
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
	// ft_print_map(&map);
	// ft_scan_map(&map);
	// if (map.closed_map == 0)
	// {
	// 	ft_free_map(&map);
	// 	return (printf(INVALID_MAP), 1);
	// }
	// else
	// {
	// 	printf("Valido\n");
	// }
    // ft_free_map(&map);
	return (0);
}
