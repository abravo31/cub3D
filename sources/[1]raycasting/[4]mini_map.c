#include "../../includes/cub3D_struct.h"

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

static int	check_elem_map(t_cub3D *data, int elem_map, int y, int x)
{
	if (elem_map == 0 || elem_map == 32 || elem_map == 'N' || elem_map == 'S'
		|| elem_map == 'W' || elem_map == 'E')
		return (1);
	else if (elem_map == 1)
		return (2);
	else if (elem_map == HORIZONTAL_DOOR)
	{
		if (data->map.door_state_map[y][x] == OPEN)
			return (1);
		else if (data->map.door_state_map[y][x] == CLOSED)
			return (3);
	}
	else if (elem_map == VERTICAL_DOOR)
	{
		if (data->map.door_state_map[y][x] == OPEN)
			return (1);
		else if (data->map.door_state_map[y][x] == CLOSED)
			return (4);
	}
	return (0);
}

static void	draw_port_vertical(t_cub3D *data, int y, int x, int square_size)
{
	int pixel_step_y;
	int pixel_step_x;
	int color;

	pixel_step_y = 0;
	while (pixel_step_y < square_size)
	{
		pixel_step_x = 0;
		while (pixel_step_x < square_size)
		{
			if (pixel_step_x == (square_size / 2))
			{
				my_mlx_pixel_put(data, (t_point){x + pixel_step_x, y + pixel_step_y, 0xFFFFFF});
			}
			else
			{
				my_mlx_pixel_put(data, (t_point){x + pixel_step_x, y + pixel_step_y, 0x7C6965});
			}
			pixel_step_x++;
		}
		pixel_step_y++;
	}
}

static void	draw_port_horizontal(t_cub3D *data, int y, int x, int square_size)
{
	int pixel_step_y;
	int pixel_step_x;
	int color;

	pixel_step_y = 0;
	while (pixel_step_y < square_size)
	{
		pixel_step_x = 0;
		if (pixel_step_y == (square_size / 2))
		{
			while (pixel_step_x < square_size)
			{
				color = 0xFFFFFF;
				my_mlx_pixel_put(data, (t_point){x + pixel_step_x, y + pixel_step_y, color});
				pixel_step_x++;
			}
		}
		else
		{
			while (pixel_step_x < square_size)
			{
				color = 0x7C6965;
				my_mlx_pixel_put(data, (t_point){x + pixel_step_x, y + pixel_step_y, color});
				pixel_step_x++;
			}
		}
		pixel_step_y++;
	}
}

void	draw_minimap(t_cub3D *data)
{
	t_vec2D	first_pixel;
	double	limit_x;
	double	limit_y;
	int		i;
	int		j;
	int		scale_map;
	int		elem_map;
	int		type_elem;


	first_pixel.x = data->rc.player.d_coords.x - 2.0;
	first_pixel.y = data->rc.player.d_coords.y - 2.0;
	i = 0;
	limit_x = first_pixel.x + (2.0 * 2);
	limit_y = first_pixel.y + (2.0 * 2);
	scale_map = 4;
	while (first_pixel.y < limit_y)
	{
		first_pixel.x = data->rc.player.d_coords.x - 2.0;
		j = 0;
		while (first_pixel.x < limit_x)
		{
			if (first_pixel.y < 0.0 || first_pixel.x < 0.0 || first_pixel.y >= data->map.max_h || first_pixel.x >= data->map.max_w)
				draw_square(data, i * scale_map, j * scale_map, 4, scale_map);
			else
			{
				elem_map = data->map.map[(int)first_pixel.y][(int)first_pixel.x];
				type_elem = check_elem_map(data, elem_map, (int)first_pixel.y, (int)first_pixel.x);
				if (type_elem == 1)
					draw_square(data, i * scale_map, j * scale_map, 4, scale_map);
				else if (type_elem == 2)
					draw_square(data, i * scale_map, j * scale_map, 5, scale_map);
				else if (type_elem == 3)
					draw_port_horizontal(data, i * scale_map, j * scale_map, scale_map);
				else if (type_elem == 4)
					draw_port_vertical(data, i * scale_map, j * scale_map, scale_map);
			}
			first_pixel.x = first_pixel.x + 0.1;
			j++;
		}
		first_pixel.y = first_pixel.y + 0.1;
		i++;
	}
}
