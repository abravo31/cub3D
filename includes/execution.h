#ifndef EXECUTION_H
# define EXECUTION_H

#include "cub3D_struct.h"

typedef struct s_point
{
	int	x;
	int	y;
	int	color;
}	t_point;

void	my_mlx_pixel_put(t_cub3D *data, t_point point);
void	place_square(t_cub3D *data, t_point point, int square_size);
void	draw_minimap(t_cub3D *data);

#endif