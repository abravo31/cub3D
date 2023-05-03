#include "execution.h"

void	place_square(t_cub3D *data, t_point point, int square_size)
{
	int x;
	int y;

	y = 0;
	while (y < square_size)
	{
		x = 0;
		while (x < square_size)
		{
			my_mlx_pixel_put(data, (t_point){point.x + x, point.y + y, point.color});
			x++;
		}
		y++;
	}

}

void	draw_minimap(t_cub3D *data)
{
	int	x;
	int	y;
	int	square_size;
	
	square_size = 7;
	y = 0;
	while (y < data->map.max_h)
	{
		x = 0;
		while (x < data->map.max_w)
		{
			if (data->map.map[y][x] == 1)
				place_square(data, (t_point){x * square_size, y * square_size, 0xFFFF00FF}, square_size);
			else if (data->map.map[y][x] == 2)
				place_square(data, (t_point){x * square_size, y * square_size, 0xFF0FF0F}, square_size);
			else if (data->map.map[y][x] == 'N' || data->map.map[y][x] == 'S' \
			|| data->map.map[y][x] == 'E' || data->map.map[y][x] == 'W')
				place_square(data, (t_point){x * square_size, y * square_size, 0xFF0000FF}, square_size);
			x++;
		}
		y++;
	}
}