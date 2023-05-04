#include "execution.h"

void	cast_ray(t_cub3D *data, t_vec2D dir_vec, t_vec2D plane_vec)
{
	t_vec2D	rayDirection;
	double	cameraX;

	// Why this ?
	cameraX = 2 * x / double(data->win_w) - 1;
	rayDirection.x = dir_vec.x + plane_vec.x * cameraX;
    rayDirection.y = dir_vec.y + plane_vec.y * cameraX;
}

void	try_raycasting(t_cub3D *data)
{
    t_vec2D dir_vec;
    t_vec2D plane_vec;
	

	dir_vec.x = -1;
    dir_vec.y = 0;
	plane_vec.x = 0;
	plane_vec.y = 0.66;
    // For each x (pixel in the screen we are going to cast a ray)
    for (int x = 0; x < data->win_w; x++)
    {
		cast_ray(data, dir_vec, plane_vec);
    }
    // double  ratio_vertical;
    // double  ratio_horizontal;
    // double  fov_v;

    // ratio_vertical = 2 * (tan(data->fov * data->win_h / (data->win_x * 2))) / 2; 
    // ratio_horizontal = (2 * tan(data->fov / 2)) / data->win_x;
    // printf("%f\n", ratio_horizontal);
}