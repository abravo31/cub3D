#include "../../includes/cub3D_struct.h"

// static void	ft_print_raycasting_params(t_rc *rc)
// {
// 	printf("Initializing...\n");
// 	printf("*******************************\n");
// 	printf("Player:\n");
// 	printf("f y %f\n", rc->player.d_coords.y);
// 	printf("f x %f\n", rc->player.d_coords.x);
// 	printf("y: %d\n", rc->player.i_coords.y);
// 	printf("x :%d\n", rc->player.i_coords.x);
// 	printf("Direction %d\n", rc->player.direction);
// 	printf("*******************************\n");
// 	printf("Direction vector:\n");
// 	printf("y %f\n", rc->dir_vec.y);
// 	printf("x %f\n", rc->dir_vec.x);
// 	printf("*******************************\n");
// 	printf("Plane vector:\n");
// 	printf("y %f\n", rc->plane_vec.y);
// 	printf("x %f\n", rc->plane_vec.x);
// 	printf("*******************************\n");
// }

static void	ft_initialize_player(t_cub3D *data, t_rc *rc)
{
	rc->player.i_coords.y = data->map.player._y;
	rc->player.i_coords.x = data->map.player._x;
	rc->player.i_coords.color = 0x00FF00;
	rc->player.d_coords.y = (double)rc->player.i_coords.y + 0.5;
	rc->player.d_coords.x = (double)rc->player.i_coords.x + 0.5;
	rc->player.direction = data->map.player._direction;
	if (rc->player.direction == 0)
		rc->player.angle_direction = 90;
	else if (rc->player.direction == 1)
		rc->player.angle_direction = 270;
	else if (rc->player.direction == 2)
		rc->player.angle_direction = 0;
	else if (rc->player.direction == 3)
		rc->player.angle_direction = 180;
}

static void	ft_init_cam(t_rc *rc)
{
	t_cam		*cam;

	cam = &rc->cam;
	cam->scale = 32;
    cam->fov = 60;
}

static void	ft_initialize_vectors(t_rc *rc)
{
	if (rc->player.direction == 0)
	{
		rc->dir_vec.x = 0;
		rc->dir_vec.y = -1;
		rc->plane_vec.x = 0.66;
		rc->plane_vec.y = 0;
	}
	else if (rc->player.direction == 1)
	{
		rc->dir_vec.x = 0;
		rc->dir_vec.y = 1;
		rc->plane_vec.x = 0.66;
		rc->plane_vec.y = 0;
	}
	else if (rc->player.direction == 2)
	{
		rc->dir_vec.x = 1;
		rc->dir_vec.y = 0;
		rc->plane_vec.x = 0;
		rc->plane_vec.y = 0.66;
	}
	if (rc->player.direction == 3)
	{
		rc->dir_vec.x = -1;
		rc->dir_vec.y = 0;
		rc->plane_vec.x = 0;
		rc->plane_vec.y = 0.66;
	}
}

void    ft_initialize_raycasting(t_cub3D *data)
{
    t_rc	*rc;

    rc = &data->rc;
	ft_initialize_player(data, rc);
	ft_init_cam(rc);
	ft_initialize_vectors(rc);
	// // ft_print_raycasting_params(rc);
	// try_raycasting(data, rc);
}