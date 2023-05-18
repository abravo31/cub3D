#include "../../includes/cub3D_struct.h"

double	vec_length(t_vec2D vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y));
}

double	dot_prod(t_vec2D vec1, t_vec2D vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y);
}

// unsigned int color_from_texture( int direction)

void	draw_column(t_cub3D *data, t_ray *ray, int x)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	cosine;

	cosine = dot_prod(ray->ray_vector, data->rc.dir_vec);
	line_height = (data->win_y / (ray->distance * cosine));
	draw_start = -line_height / 2 + data->mid_y;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + data->mid_y;
	if (draw_end >= data->win_y)
		draw_end = data->win_y - 1;
	while (draw_start <= draw_end)
	{
		// if (ray->orientation_wall_hit == N)
		// {
		my_mlx_pixel_put(data, (t_point){x, draw_start, 0xFFFFFF});//color_from_texture(ray->orientation_wall_hit)});
		// }
		// else if (ray->orientation_wall_hit == S)
		// {
			// my_mlx_pixel_put(data, (t_point){x, draw_start, 0x00FFFF});
		// }
		// else if (ray->orientation_wall_hit == E)
		// {
			// my_mlx_pixel_put(data, (t_point){x, draw_start, 0xFF00FF});
		// }
		// else if (ray->orientation_wall_hit == W)
		// {
			// my_mlx_pixel_put(data, (t_point){x, draw_start, 0xFFFF00});
		// }
		draw_start++;
	}
}

unsigned int	find_color(t_list	*ident_fc, int type)
{
	while (ident_fc && ((t_fc *)(ident_fc->content))->id != type)
		ident_fc = ident_fc->next;
	return (((t_fc *)(ident_fc->content))->r << 16 \
	| ((t_fc *)(ident_fc->content))->g << 8 \
	| ((t_fc *)(ident_fc->content))->b);
}

t_texture	find_texture(t_cub3D *data, t_list	*ident_coord, int type)
{
	char		*path;
	t_texture	texture;

	while (ident_coord && ((t_coord *)(ident_coord->content))->id != type)
		ident_coord = ident_coord->next;
	path = ((t_coord *)(ident_coord->content))->path;
	texture = (t_texture){NULL, NULL, 0, 0, 0, 0, 0};
	texture.img = mlx_xpm_file_to_image(data->mlx, path, \
	&texture.img_width, &texture.img_height);
	if (texture.img == NULL)
		return (printf(MLX_ERROR), ft_exit(data), texture);
	texture.addr = mlx_get_data_addr(texture.img, &texture.bpp, &texture.line_len, &texture.endian);
	if (texture.addr == NULL)
		return (mlx_destroy_image(data->mlx, texture.img), \
		printf(MLX_ERROR), ft_exit(data), texture);
	// mlx_destroy_image(data->mlx, texture.img);
	return (texture);
}

void	draw_scene(t_cub3D *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->win_y)
	{
		x = 0;
		while (x < data->win_x)
		{
			if (y < data->mid_y)
				my_mlx_pixel_put(data, (t_point){x, y, data->background_colors[1]});
			else
				my_mlx_pixel_put(data, (t_point){x, y, data->background_colors[0]});
			x++;
		}
		y++;
	}
}
