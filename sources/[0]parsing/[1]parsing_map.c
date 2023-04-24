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
			printf("%d ", map->map[i][j]);
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

void	ft_scan_point_area(int **map, int x, int y, int max_w, int max_h)
{
	if ((x < 0 || x == max_w) && (y < 0 || y == max_h))
		return ;
	if (map[y][x] == '0')
	{
		printf("%c\n", map[y][x]);
	}
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
			ft_scan_point_area(map->map, j, i, map->max_width, map->max_heigth);
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
	// ft_scan_map(&map);
    ft_free_map(&map); 
}
