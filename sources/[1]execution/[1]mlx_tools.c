#include "execution.h"

void	my_mlx_pixel_put(t_cub3D *data, t_point point)
{
	int	dst;

	if (point.x >= 0 && point.x <= 1920 && point.y >= 0 && point.y <= 1080)
	{
		dst = ((int)point.y * data->line_len) + ((int)point.x * (data->bpp / 8));
		data->addr[dst] = point.color;
		data->addr[++dst] = point.color >> 8;
		data->addr[++dst] = point.color >> 16;
	}
}
