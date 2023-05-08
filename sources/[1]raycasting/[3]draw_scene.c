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

	int	y;
	int	x;
	int i;
	int j;

	// printf("int y %d\n", data->player.i_coords.y);
	// printf("int x %d\n", data->player.i_coords.x);
	// printf("f y %f\n", data->player.d_coords.y);
	// printf("f x %f\n", data->player.d_coords.x);
	// printf("f * scale y %d\n", (int)(data->player.d_coords.y * data->map.scale));
	// printf("f *scale x %d\n", (int)(data->player.d_coords.x * data->map.scale));
	y = (int)(data->player.d_coords.y * data->map.scale);
	x = (int)(data->player.d_coords.x * data->map.scale);
	// printf("y: %d\n", y);
	// printf("x :%d\n", x);
	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			my_mlx_pixel_put(data, (t_point){x + j, y + i, data->player.i_coords.color});
			j++;
		}
		i++;
	}
}

static void	draw_dir_vector(t_cub3D *data)
{
	t_vec2D	dir_vec;
	t_vec2D	res_vector;
	
	// To the north
	dir_vec.x = 0;
	dir_vec.y = 1;
	printf("%f - %f\n", data->player.d_coords.y, data->player.d_coords.x);
	res_vector = add_2D_vec(data->player.d_coords, dir_vec);
	printf("res : %f - %f\n", res_vector.y, res_vector.x);
	ft_draw_line(data, data->player.d_coords, res_vector);
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

	my_mlx_pixel_put(data, (t_point){x + 0, y + 0, 0xFFFFFF});
	pixel_step_y = 1;
	while (pixel_step_y < square_size)
	{
		// my_mlx_pixel_put(data, (t_point){x + 0, y + pixel_step_y, 0xFFFFFF});
		pixel_step_x = 1;
		while (pixel_step_x < square_size)
		{
			if (obj == 1)
				color = 0xFFFF00FF;
			else if (obj == 2)
				color = 0xFF0FF0F;
			else
				color = 0xFF0000FF;
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

