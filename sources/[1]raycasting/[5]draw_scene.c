#include "../../includes/cub3D_struct.h"

static void	ft_bresenham(t_cub3D *data, t_line *line)
{
	double	t;
	double	current_x;
	double	current_y;
	int		i;

	i = 0;
	while (i <= line->length)
	{
		t = (double)i / line->length;
		current_x = line->x1 + (t * (line->x2 - line->x1));
		current_y = line->y1 + (t * (line->y2 - line->y1));
		my_mlx_pixel_put(data, (t_point){current_x, current_y, 0xFF0000});
		i++;
	}
}

static void	ft_draw_line(t_cub3D *data, t_vec2D vec_1, t_vec2D vec_2)
{
	t_line	line;

	(void)data;
	line.x1 = (int)vec_1.x;
	line.y1 = (int)vec_1.y;
	line.x2 = (int)vec_2.x;
	line.y2 = (int)vec_2.y;
	line.dx = ft_abs_2_values(line.x2, line.x1);
	line.dy = ft_abs_2_values(line.y2, line.y1);
	if (line.dx > line.dy)
		line.length = line.dx;
	else
		line.length = line.dy;
	// printf("length : %d\n", line.length);
	ft_bresenham(data, &line);
}

static void	draw_square_player(t_cub3D *data)
{
	t_player	player;
	int	y;
	int	x;
	int i;
	int j;

	player = data->rc.player;
	y = (int)(player.d_coords.y * data->rc.cam.scale);
	x = (int)(player.d_coords.x * data->rc.cam.scale);
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

static void	draw_dir_vector(t_cub3D *data)
{
	t_vec2D		res_vector;
	t_vec2D		player_screen;
	t_player	player;



	player = data->rc.player;
	// printf("Player -> y : %f - x : %f\n", player.d_coords.y, player.d_coords.x);
	printf("Direction vector -> y: %f - x : %f\n", data->rc.dir_vec.y, data->rc.dir_vec.x);
	data->rc.dir_vec = rotate_2D_vector(data->rc.dir_vec, player.angle_direction);
	printf("Direction vector -> y: %f - x : %f\n", data->rc.dir_vec.y, data->rc.dir_vec.x);
	res_vector = add_2D_vec(player.d_coords, data->rc.dir_vec);
	// printf("res : %f - %f\n", res_vector.y, res_vector.x);
	res_vector.y *= data->rc.cam.scale;
	res_vector.x *= data->rc.cam.scale;
	player_screen.y = player.d_coords.y * data->rc.cam.scale;
	player_screen.x = player.d_coords.x * data->rc.cam.scale;
	ft_draw_line(data, player_screen, res_vector);
}

void	draw_player(t_cub3D *data)
{
	draw_square_player(data);
	draw_dir_vector(data);
}

static void	draw_square(t_cub3D *data, int y, int x, int obj, int square_size)
{
	int pixel_step_y;
	int pixel_step_x;
	int color;

	my_mlx_pixel_put(data, (t_point){x + 0, y + 0, 0x000000});
	pixel_step_y = 1;
	while (pixel_step_y < square_size)
	{
		// my_mlx_pixel_put(data, (t_point){x + 0, y + pixel_step_y, 0xFFFFFF});
		pixel_step_x = 1;
		while (pixel_step_x < square_size)
		{
			if (obj == 1)
				color = 0x0000FF;
			else if (obj == 2)
				color = 0x0FF000;
			else
				color = 0xFFFFFF;
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

	scale_map = data->rc.cam.scale;
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
	draw_minimap_grid(data);
	draw_player(data);
}

