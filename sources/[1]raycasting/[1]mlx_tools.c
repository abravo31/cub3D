#include "../../includes/cub3D_struct.h"

void	my_mlx_pixel_put(t_cub3D *data, t_point point)
{
	int		dst;
	t_image	*img;

	img = &data->img;
	if (point.x >= 0 && point.x <= 1920 && point.y >= 0 && point.y <= 1080)
	{
		dst = ((int)point.y * img->line_len) + ((int)point.x * (img->bbp / 8));
		// *(int *)(img->addr + (int)(dst)) = point.color;
		img->addr[dst] = point.color;
		img->addr[++dst] = point.color >> 8;
		img->addr[++dst] = point.color >> 16;
	}
}
