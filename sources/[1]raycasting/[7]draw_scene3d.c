#include "../../includes/cub3D_struct.h"

double	vec_length(t_vec2D vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y));
}

double	dot_prod(t_vec2D vec1, t_vec2D vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y);
}

static inline int	idx(int row, int col, int dim)
{
	return ((row * dim) + col);
}

int color_from_texture(t_cub3D *data, int direction, double xpercent, int y)
{
	t_texture	texture;
	int			x;
	// int			y;

	if (direction < 1 || direction > 4)
	{
		printf("directionwrong: %d\n", direction);
		direction = 1;
	}
	texture = data->wall_textures[direction - 1];
	if (y > texture.img_height)
	{
		// printf("ybig: %d, height: %d\n", y, texture.img_height);
		y = texture.img_height;
	}
	if (y < 0)
	{
		// printf("ysmall: %d, height: %d\n", y, texture.img_height);
		y = 0;
	}
	x = texture.img_width * xpercent;
	if (x > texture.img_width)
	{
		// printf("xbig: %d\n", x);
		x = texture.img_width;
	}
	if (x < 0)
	{
		// printf("xsmall: %d\n", x);
		x = 0;
	}
	return (((int *)texture.addr)[idx(y, x, texture.line_len / sizeof(int))]);
}

int color_from_texture_back(t_cub3D *data, double xpercent, double ypercent)
{
	t_texture	texture;
	int			x;
	int			y;

	texture = data->wall_textures[0];
	y = texture.img_height * ypercent;
	x = texture.img_width * xpercent;
	return (((int *)texture.addr)[idx(y, x, texture.line_len / sizeof(int))]);
}

// int	is_inter(int x, int y, double cosine, t_cub3D *data, t_ray *ray)
// {
// 	double distance;
// 	t_vec2D curr_coord;

// 	distance = data->win_y / (2 * cosine * (data->mid_y - y));

// 	curr_coord = add_2D_vec(data->rc.player.d_coords, scalar_mult(ray->ray_vector, distance));
// 	if (ft_abs_double(curr_coord.x - (float)((int)curr_coord.x)) < 0.01 &&
// 		ft_abs_double(curr_coord.y - (float)((int)curr_coord.y)) < 0.01)
// 		return (0);
// 	return (1);
// }

void	draw_ceiling(int end, t_cub3D *data, int x, double cosine, t_ray *ray)
{
	int	start;
	double distance;
 	t_vec2D curr_coord;
	double xpercent;
	double ypercent;

	
	start = 0;
	xpercent = 0.0;
	ypercent = 0.0;
	while (start < end)
	{
		distance = data->win_y / (2 * cosine * (data->mid_y - start));
		curr_coord = add_2D_vec(data->rc.player.d_coords, scalar_mult(ray->ray_vector, distance));
		xpercent = curr_coord.x - (float)((int)curr_coord.x);
		ypercent = curr_coord.y - (float)((int)curr_coord.y);
		my_mlx_pixel_put(data, (t_point){x, start, color_from_texture_back(data, xpercent, ypercent)});
		start++;
	}
}
// int	dist_from_point(t_cub3D *data, int x, int y)
// {
// 	int	distance;

// 	return (distance);
// }

// int	get_floor_color(t_cub3D *data, int x, int y)
// {
// 	int	distance;
// 	int	color;

// 	color = 0;
// 	distance = dist_from_point(data, x, y);
// 	/*calcul de couleurs avec distance*/
// 	return (color);
// }

void draw_floor(int start, t_cub3D *data, int x, double cosine, t_ray *ray)
{
	double distance;
	t_vec2D curr_coord;
	double xpercent;
	double ypercent;

	while (start <= data->win_y)
	{
		distance = data->win_y / (2 * cosine * (start - data->mid_y));
		curr_coord = add_2D_vec(data->rc.player.d_coords, scalar_mult(ray->ray_vector, distance));
		xpercent = curr_coord.x - (float)((int)curr_coord.x);
		ypercent = curr_coord.y - (float)((int)curr_coord.y);
		my_mlx_pixel_put(data, (t_point){x, start, color_from_texture_back(data, xpercent, ypercent)});
		start++;
	}
}

void	draw_column(t_cub3D *data, t_ray *ray, int x)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	texpos;
	double	step;
	double	xpercent;
	double	ypercent;
	int		begin;
	double	cosine;
	t_point	point;

	cosine = dot_prod(ray->ray_vector, data->rc.dir_vec);
	line_height = (data->win_y / (ray->distance * cosine));
	draw_start = -line_height / 2 + data->mid_y;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + data->mid_y;
	if (draw_end >= data->win_y)
		draw_end = data->win_y - 1;
	begin = draw_start;
	step = 1.0 * data->wall_textures[ray->orientation_wall_hit - 1].img_height / line_height;
	texpos = (draw_start - data->mid_y + line_height / 2) * step;
	draw_ceiling(draw_start, data, x, cosine, ray);
	while (draw_start <= draw_end)
	{
		if (ray->orientation_wall_hit == 1 || ray->orientation_wall_hit == 2)
			xpercent = (ray->hit_point.x - (float)((int)ray->hit_point.x));
		else
			xpercent = (ray->hit_point.y - (float)((int)ray->hit_point.y));
		texpos += step;
		point = (t_point){x, draw_start, \
		color_from_texture(data, ray->orientation_wall_hit, xpercent, texpos)};
		my_mlx_pixel_put(data, point);
		draw_start++;
	}
	draw_floor(draw_start, data, x, cosine, ray);
}

unsigned int	find_color(t_list *ident_fc, int t)
{
	while (ident_fc && ((t_fc *)(ident_fc->content))->id != t)
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
	return (texture);
}

// void	draw_scene(t_cub3D *data)
// {
// 	// int	x;
// 	// int	y;

// 	// y = 0;
// 	// while (y < data->win_y)
// 	// {
// 	// 	x = 0;
// 	// 	while (x < data->win_x)
// 	// 	{
// 	// 		if (y < data->mid_y)
// 	// 			my_mlx_pixel_put(data, (t_point){x, y, data->background_colors[1]});
// 	// 		else
// 	// 			my_mlx_pixel_put(data, (t_point){x, y, data->background_colors[0]});
// 	// 		x++;
// 	// 	}
// 	// 	y++;
// 	// }
// }
