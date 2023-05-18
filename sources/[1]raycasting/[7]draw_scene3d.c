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

unsigned int color_from_texture(t_cub3D *data, int direction, double xpercent, double ypercent)
{
	t_texture	texture;
	int			y;
	int			x;

	texture = data->wall_textures[direction];
	y = data->win_y * ypercent;
	x = data->win_x * xpercent;
	// xpercent = (double)x / (double)texture.img_height
	// x = xpercent * data->
	return (*(int *)(texture.addr + idx(y, x, texture.img_width)));
}

void	draw_column(t_cub3D *data, t_ray *ray, int x)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
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
	while (draw_start <= draw_end)
	{
		point = (t_point){x, draw_start, \
		color_from_texture(data, ray->orientation_wall_hit - 1, \
		0.253, (double)(draw_start - begin) / (double)(draw_end - begin))};
		my_mlx_pixel_put(data, point);
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
