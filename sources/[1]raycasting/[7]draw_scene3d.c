#include "../../includes/cub3D_struct.h"

void	draw_column(t_cub3D *data, t_ray *ray, int x)
{
	int	line_height;
	int	draw_start;
	int	draw_end;

	line_height = (data->win_y / ray->distance);
	draw_start = -line_height / 2 + data->mid_y;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + data->mid_y;
	if (draw_end >= data->win_y)
		draw_end = data->win_y - 1;
	while (draw_start <= draw_end)
	{
		if (ray->orientation_wall_hit == N)
		{
			my_mlx_pixel_put(data, (t_point){x, draw_start, 0xFFFFFF});
			// printf("hello\n");
		}
		else if (ray->orientation_wall_hit == S)
		{
			// printf("direction: %d\n", ray->orientation_wall_hit);
			my_mlx_pixel_put(data, (t_point){x, draw_start, 0x00FFFF});

		}
		else if (ray->orientation_wall_hit == E)
		{
			my_mlx_pixel_put(data, (t_point){x, draw_start, 0xFF00FF});
		}
		else if (ray->orientation_wall_hit == W)
		{
			my_mlx_pixel_put(data, (t_point){x, draw_start, 0xFFFF00});
		}
		draw_start++;
	}
}


// //choose wall color
// ColorRGB color;
// switch(worldMap[mapX][mapY])
// {
//     case 1:  color = RGB_Red;  break; //red
//     case 2:  color = RGB_Green;  break; //green
//     case 3:  color = RGB_Blue;   break; //blue
//     case 4:  color = RGB_White;  break; //white
//     default: color = RGB_Yellow; break; //yellow
// }

//       //give x and y sides different brightness
//       if (side == 1) {color = color / 2;}

//       //draw the pixels of the stripe as a vertical line
//       verLine(x, drawStart, drawEnd, color);
// }

void	draw_scene_3D(t_cub3D *data)
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