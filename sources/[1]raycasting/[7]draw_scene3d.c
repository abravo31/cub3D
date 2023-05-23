#include "../../includes/cub3D_struct.h"

void	draw_ceiling(t_cub3D *data, int x, double cosine, t_ray *ray)
{
	int		start;
	double	distance;
	t_vec2D	curr_coord;
	double	xpercent;
	double	ypercent;

	start = 0;
	while (start < data->draw_start)
	{
		distance = data->win_y / (2 * cosine * (data->mid_y - start));
		curr_coord = add_2D_vec(data->rc.player.d_coords, \
		scalar_mult(ray->ray_vector, distance));
		xpercent = ft_abs_double(curr_coord.x - (int)curr_coord.x);
		ypercent = ft_abs_double(curr_coord.y - (int)curr_coord.y);
		my_mlx_pixel_put(data, (t_point){x, start, \
		ceiling_floor_color(data, xpercent, ypercent, 5)});
		start++;
	}
}

void	draw_floor(t_cub3D *data, int x, double cosine, t_ray *ray)
{
	double	distance;
	t_vec2D	curr_coord;
	double	xpercent;
	double	ypercent;
	int		start;

	start = data->draw_end;
	if (start == data->mid_y)
		start++;
	while (start < data->win_y)
	{
		distance = data->win_y / (2 * cosine * (start - data->mid_y));
		curr_coord = add_2D_vec(data->rc.player.d_coords, \
		scalar_mult(ray->ray_vector, distance));
		xpercent = ft_abs_double(curr_coord.x - (int)curr_coord.x);
		ypercent = ft_abs_double(curr_coord.y - (int)curr_coord.y);
		my_mlx_pixel_put(data, (t_point){x, start, \
		ceiling_floor_color(data, xpercent, ypercent, 4)});
		start++;
	}
}

void	loop_draw_wall(t_cub3D *data, int line_height, int x, t_ray *ray)
{
	double	texpos;
	double	step;
	double	xpercent;
	t_point	point;

	step = 1.0 * \
	data->wall_textures[ray->orientation_wall_hit - 1].img_height / line_height;
	texpos = (data->draw_start - data->mid_y + line_height / 2) * step;
	while (data->draw_start <= data->draw_end)
	{
		if (ray->orientation_wall_hit == 1 || ray->orientation_wall_hit == 2)
			xpercent = (ray->hit_point.x - (float)((int)ray->hit_point.x));
		else
			xpercent = (ray->hit_point.y - (float)((int)ray->hit_point.y));
		texpos += step;
		point = (t_point){x, data->draw_start, \
		color_from_texture(data, ray->orientation_wall_hit, xpercent, texpos)};
		my_mlx_pixel_put(data, point);
		data->draw_start++;
	}
}

void	draw_column(t_cub3D *data, t_ray *ray, int x)
{
	int		line_height;
	double	cosine;

	cosine = dot_prod(ray->ray_vector, data->rc.dir_vec);
	line_height = (data->win_y / (ray->distance * cosine));
	data->draw_start = -line_height / 2 + data->mid_y;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = line_height / 2 + data->mid_y;
	if (data->draw_end >= data->win_y)
		data->draw_end = data->win_y - 1;
	if (line_height < data->win_y)
	{
		draw_ceiling(data, x, cosine, ray);
		draw_floor(data, x, cosine, ray);
	}
	loop_draw_wall(data, line_height, x, ray);
}
