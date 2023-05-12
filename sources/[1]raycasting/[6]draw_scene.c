#include "../../includes/cub3D_struct.h"

static void	draw_square_player(t_cub3D *data, t_rc *rc)
{
	t_player	player;
	int	y;
	int	x;
	int i;
	int j;

	player = rc->player;
	y = (int)(player.d_coords.y * rc->scale_map);
	x = (int)(player.d_coords.x * rc->scale_map);
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

static void	print_vec_info(t_vec2D vec, char *msg)
{
	printf("%s ", msg);
	printf("x -> %f | y -> %f\n", vec.x, vec.y);
}

static void	draw_vectors(t_cub3D *data, t_rc *rc)
{
	t_player	*player_ptr;
	t_vec2D		vector_center_screen;
	t_vec2D		vector_per_screen;
	t_vec2D		vector_per_screen_opposite;
	t_vec2D		player_screen;

	player_ptr = &rc->player;
	player_screen = player_ptr->d_coords;
	// Getting player position in the screen
	player_screen = scalar_mult(player_screen, rc->scale_map);
	// Getting and drawing player + dir in the screen
	vector_center_screen = scalar_mult(rc->center_screen, rc->scale_map);
	ft_draw_line(data, player_screen, vector_center_screen, 0xFF0000);
	// Getting perpendicular vector from the screen
	vector_per_screen = add_2D_vec(rc->center_screen, rc->per_vec);
	vector_per_screen = scalar_mult(vector_per_screen, rc->scale_map);
	// ft_draw_line(data, player_screen, vector_per_screen, 0xFF0000);
	// Getting perpendicular opposite from the screen
	vector_per_screen_opposite = subtract_2D_vec(rc->center_screen, rc->per_vec);
	vector_per_screen_opposite = scalar_mult(vector_per_screen_opposite, rc->scale_map);
	// ft_draw_line(data, player_screen, vector_per_screen_opposite, 0xFF0000);
}

void	draw_player(t_cub3D *data)
{
	t_rc	*rc;

	rc = &data->rc;
	draw_square_player(data, rc);
	draw_vectors(data, rc);
}

void	draw_square(t_cub3D *data, int y, int x, int obj, int square_size)
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
			else if (obj == 3)
				color = 0xFFA500;
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

	scale_map = data->rc.scale_map;
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