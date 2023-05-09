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