#include "../../includes/cub3D_struct.h"

void	draw_player(t_cub3D *data, t_player player)
{
	int	y;
	int	x;
	int i;
	int j;

	y = player.d_coords.y * data->map.scale;
	x = player.d_coords.x * data->map.scale;
	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			my_mlx_pixel_put(data, (t_point){x + j, y + i, player.i_coords.color});
			j++;
		}
		i++;
	}
}

static void	draw_square(t_cub3D *data, int y, int x, int obj, int square_size)
{
	int pixel_step_y;
	int pixel_step_x;
	int color;

	color = 0xFF0FF0F;
	(void)data;
	printf("y : %d -- x %d\n", y, x);
	// my_mlx_pixel_put(data, (t_point){x + 0, y + 0, 0xFFFFFF});
	pixel_step_y = 0;
	while (pixel_step_y < square_size)
	{
		// my_mlx_pixel_put(data, (t_point){x + 0, y + pixel_step_y, 0xFFFFFF});
		pixel_step_x = 0;
		while (pixel_step_x < square_size)
		{
			// if (obj == 1)
			// 	color = 0xFFFF00FF;
			// else if (obj == 2)
			// 	color = 0xFF0FF0F;
			// else
			// 	color = 0xFF0000FF;
			// printf("x + pixel_step_x %d | y + pixel_step_y %d\n", x + pixel_step_x, y + pixel_step_y);
			// printf("%d\n", color);
			my_mlx_pixel_put(data, (t_point){x + pixel_step_x, y + pixel_step_y, color});
			pixel_step_x++;
		}
		pixel_step_y++;
	}
}

static void	draw_minimap_grid(t_cub3D *data)
{
	int		x;
	int		y;
	int		scale_map;

	scale_map = data->map.scale;
	printf("%d\n", scale_map);
	y = 0;
	while (y < data->map.max_h)
	{
		x = 0;
		while (x < data->map.max_w)
		{
			draw_square(data, y * scale_map, x * scale_map, data->map.map[y][x], scale_map);
			x++;
		}
		y++;
	}
}

void	draw_scene(t_cub3D *data)
{
	t_player player;

	player.i_coords.y = data->map.player._y;
	player.i_coords.x = data->map.player._x;
	player.i_coords.color = 0x00FF00;
	player.d_coords.y = (double)player.i_coords.y + 0.5;
	player.d_coords.x = (double)player.i_coords.x + 0.5;
	draw_minimap_grid(data);
	draw_player(data, player);
}