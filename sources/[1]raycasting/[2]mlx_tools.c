#include "../../includes/cub3D_struct.h"

// void	my_mlx_pixel_put(t_cub3D *data, t_point point)
// {
// 	int		dst;
// 	t_image	*img;

// 	img = &data->img;
// 	if (point.x >= 0 && point.x <= 1920 && point.y >= 0 && point.y <= 1080)
// 	{
// 		dst = ((int)point.y * img->line_len) + ((int)point.x * (img->bbp / 8));
// 		// *(int *)(img->addr + (int)(dst)) = point.color;
// 		img->addr[dst] = point.color;
// 		img->addr[++dst] = point.color >> 8;
// 		img->addr[++dst] = point.color >> 16;
// 	}
// }

static int	idx(int row, int col, int dim)
{
	return ((row * dim) + col);
}

void	my_mlx_pixel_put(t_cub3D *data, t_point point)
{
	t_image	*img;
	int		index;

	img = &data->img;
	if (point.x >= 0 && point.x <= data->win_x && point.y >= 0 && point.y <= data->win_y)
	{
		index = idx(point.y + img->offset_window_y, point.x + img->offset_window_x, data->win_x) * (img->bbp / 8);
		*(int *)(img->addr + (int)(index)) = point.color;
	}
}

void	ft_bresenham(t_cub3D *data, t_line *line)
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
		my_mlx_pixel_put(data, (t_point){current_x, current_y, line->color});
		i++;
	}
}

void	ft_draw_line(t_cub3D *data, t_vec2D vec_1, t_vec2D vec_2, int color)
{
	t_line	line;

	line.x1 = (int)vec_1.x;
	line.y1 = (int)vec_1.y;
	line.x2 = (int)vec_2.x;
	line.y2 = (int)vec_2.y;
	line.dx = ft_abs_2_values(line.x2, line.x1);
	line.dy = ft_abs_2_values(line.y2, line.y1);
	line.color = color;
	if (line.dx > line.dy)
		line.length = line.dx;
	else
		line.length = line.dy;
	ft_bresenham(data, &line);
}

void	draw_square_point(t_cub3D *data, t_vec2D point)
{
	t_vec2D	point_screen;

	point_screen = scalar_mult(point, data->rc.scale_map);
	draw_square(data, (int)point_screen.y, (int)point_screen.x, 4, 5);
}