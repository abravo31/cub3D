#include "../../includes/cub3D_struct.h"

static int  ft_check_player_can_move(t_map *map, int y, int x)
{
    int moves;

    moves = 0;
    if (map->map[y + 1][x] == 0)
		moves++;
	if (map->map[y - 1][x] == 0)
		moves++;
	if (map->map[y][x + 1] == 0)
		moves++;
	if (map->map[y][x - 1] == 0)
		moves++;
	if (moves == 0)
		return (1);
	return (0);
}

int	ft_check_player(t_map *map, int c_player, int y, int x)
{
	if (c_player == 'N' || c_player == 'S' || c_player == 'E' || c_player == 'W')
	{
		if (y == 0 || y == (map->max_h - 1))
			return (printf(PLAYER_IN_EDGE), 1);
		else if (x == 0 || x == (map->max_w - 1))
			return (printf(PLAYER_IN_EDGE), 1);
		if (!map->player._is_set)
		{
			map->player._direction = 0;
			map->player._y = y;
			map->player._x = x;
			map->player._is_set = 1;
			if (ft_check_player_can_move(map, y, x))
				return (printf(PLAYER_CANT_MOVE), 1);
		}
		else
			return (printf(DOUBLE_PLAYER), 1);
	}
	return (0);
}
