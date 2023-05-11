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

static void	draw_vectors(t_cub3D *data, t_rc *rc)
{
	t_player	*player_ptr;
	t_vec2D		vector_dir_screen;
	t_vec2D		vec_plane_screen_1;
	t_vec2D		vec_plane_screen_2;
	t_vec2D		player_screen;

	(void)data;
	player_ptr = &rc->player;
	player_screen = player_ptr->d_coords;
	vector_dir_screen = add_2D_vec(player_screen, rc->dir_vec);
	vec_plane_screen_1 = add_2D_vec(vector_dir_screen, rc->per_vec);
	// vec_aux_plane = scalar_mult(vec_plane_screen_1, 2);
	vec_plane_screen_2 = subtract_2D_vec(vector_dir_screen, rc->per_vec);
	// printf("*******************************************************\n");
	// printf("Player vector 		-> y: %f - x : %f\n", player_ptr->d_coords.y, player_ptr->d_coords.x);
	// printf("Direction vector 	-> y: %f - x : %f\n", rc->dir_vec.y, rc->dir_vec.x);
	// printf("Plane vector 		-> y: %f - x : %f\n", rc->per_vec.y, rc->per_vec.x);
	// printf("/////////////////////////////////////////////////////////\n");
	// printf("Direction vector + player_ptr -> y: %f - x : %f\n", vector_dir_screen.y, vector_dir_screen.x);
	// printf("Direction vector + player_ptr + plane vector y: %f - x : %f\n", vec_plane_screen_1.y, vec_plane_screen_1.x);
	// printf("Direction vector + player_ptr + plane vector y: %f - x : %f\n", vec_plane_screen_2.y, vec_plane_screen_2.x);
	// printf("\n\n");
	vector_dir_screen = scalar_mult(vector_dir_screen, rc->scale_map);
	vec_plane_screen_1 = scalar_mult(vec_plane_screen_1, rc->scale_map);
	vec_plane_screen_2 = scalar_mult(vec_plane_screen_2, rc->scale_map);
	player_screen = scalar_mult(player_screen, rc->scale_map);
	ft_draw_line(data, player_screen, vector_dir_screen, 0xFF0000);
	// ft_draw_line(data, player_screen, vec_plane_screen_1, 0xFF0000);
	// ft_draw_line(data, vec_plane_screen_1, vector_dir_screen, 0xFF0000);
	// ft_draw_line(data, vec_plane_screen_2, vector_dir_screen, 0xFF0000);
	// ft_draw_line(data, player_screen, vec_plane_screen_2, 0xFF0000);
}

void	draw_player(t_cub3D *data)
{
	t_rc	*rc;

	rc = &data->rc;
	draw_square_player(data, rc);
	draw_vectors(data, rc);
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