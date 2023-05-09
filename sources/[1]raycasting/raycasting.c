#include "../../includes/cub3D_struct.h"

static void	ft_clear_img(t_cub3D *data)
{
	ft_bzero(data->img.addr, data->win_x * data->win_y * (data->img.bbp / 8));
}

// static void	try_raycasting(t_cub3D *data, t_rc *rc)
// {
// 	t_vec2D	rayDir;
// 	t_vec2D deltaDist;
// 	t_vec2D	sideDist;
// 	double	cameraX;
// 	int		current_x;
// 	int		mapX = (int)rc->player.i_coords.x;
//     int 	mapY = (int)rc->player.i_coords.y;
	
// 	double perpWallDist;
// 	//what direction to step in x or y-direction (either +1 or -1)
// 	int stepX;
// 	int stepY;
// 	int hit = 0; //was there a wall hit?
// 	int side; //was a NS or a EW wall hit?

// 	printf("mapX %d -- mapY %d\n", mapX, mapY);
// 	current_x = 0;
// 	while (current_x < data->map.max_w)
// 	{
// 		cameraX = 2 * current_x / (double)(data->map.max_w) - 1;
// 		rayDir.x = rc->dir_vec.x + rc->plane_vec.x * cameraX;
//     	rayDir.y = rc->dir_vec.y + rc->plane_vec.y * cameraX;
// 		// printf("rayDirX %f -- rayDirY %f\n", rayDir.x, rayDir.y);
// 		deltaDist.x = ft_abs_double(1 / rayDir.x);
//     	deltaDist.y = ft_abs_double(1 / rayDir.y);
// 		// printf("deltaDistX %f -- deltaDistY %f\n", deltaDist.x, deltaDist.y);
// 		if(rayDir.x < 0)
// 		{
// 			stepX = -1;
// 			sideDist.x = (rc->player.i_coords.x - mapX) * deltaDist.x;
// 		}
// 		else
// 		{
// 			stepX = 1;
// 			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
// 		}
// 		if(rayDirY < 0)
// 		{
// 			stepY = -1;
// 			sideDistY = (posY - mapY) * deltaDistY;
// 		}
// 		else
// 		{
// 			stepY = 1;
// 			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
// 		}
// 		current_x++;
// 	}
// }

// static void	try_raycasting(t_cub3D *data, t_rc *rc)
// {

// }

void	render(t_cub3D *data)
{
	ft_clear_img(data);
	draw_scene(data);
	// try_raycasting(data, data->rc);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
}


// void dda(t_cub3D *data)
// {

// }


static t_vec2D	ft_get_perpendicular_vec(t_vec2D dir_vec)
{
	t_vec2D	res_perpendicular_vec;
	double	norm;

	norm = sqrt(1 + (((dir_vec.x * dir_vec.x) / (dir_vec.y * dir_vec.y))));
	res_perpendicular_vec.x = -1 / norm;
	res_perpendicular_vec.y = ((dir_vec.x) / dir_vec.y) / norm;
	printf("perpendicular x %f - y %f\n", res_perpendicular_vec.x, res_perpendicular_vec.y);
	return (res_perpendicular_vec);
}

void init_dda(t_cub3D *data)
{
	int		i;
	t_vec2D	res_perpendicular_vec;
	t_vec2D	current_ray;

	printf("Direction vector -> y: %f - x : %f\n", data->rc.dir_vec.y, data->rc.dir_vec.x);
	res_perpendicular_vec = ft_get_perpendicular_vec(data->rc.dir_vec);
	printf("Perpendicular vector -> y: %f - x : %f\n", res_perpendicular_vec.y, res_perpendicular_vec.x);
	i = 0;
	while (i <= data->win_x)
	{
		current_ray = scalar_mult(res_perpendicular_vec, tan(data->rc.fov / 2) - (data->rc.ray_dist * i));
		printf("current_ray x %f -- y %f\n", current_ray.x, current_ray.y);
		i++;
	}
}

int	lauch_raycasting(t_cub3D *data)
{
	if (setup_mlx_env(data))
		return (ft_exit_and_free(data, 1, NULL, MLX_ERROR), 1);
	ft_initialize_raycasting(data);
	init_dda(data);
	setup_controls_hooks(data);
	render(data);
	mlx_loop(data->mlx);
	return (0);
}
