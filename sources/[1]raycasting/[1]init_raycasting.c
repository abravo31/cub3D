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
	rc->player.d_coords.y = (double)rc->player.i_coords.y + 0.5;
	rc->player.d_coords.x = (double)rc->player.i_coords.x + 0.5;
	rc->player.direction = data->map.player._direction;
}

static void	ft_initialize_vectors(t_cub3D *data, t_rc *rc)
{
	rc->dir_vec.x = 1;
	rc->dir_vec.y = 0;
	if (rc->player.direction == 0)
		rc->dir_vec = rotate_2D_vector(rc->dir_vec, 270.0);
	else if (rc->player.direction == 1)
		rc->dir_vec = rotate_2D_vector(rc->dir_vec, 90.0);
	else if (rc->player.direction == 2)
		rc->dir_vec = rotate_2D_vector(rc->dir_vec, 0.0);
	else if (rc->player.direction == 3)
		rc->dir_vec = rotate_2D_vector(rc->dir_vec, 180.0);
	// rc->scale_map = 150;
	rc->scale_map = 40;
    rc->fov = ft_deg_to_rad((double)60);
	rc->ray_dist = (2 * tan(rc->fov / 2)) / data->win_x;
	// printf("fov : %f\n", rc->fov);
	// printf("tan : %f\n", (2 * tan(rc->fov / 2)));
	// printf("ray_dist : %f\n", rc->ray_dist);
}

void    ft_initialize_raycasting(t_cub3D *data)
{
    t_rc	*rc;

    rc = &data->rc;
	ft_initialize_player(data, rc);
	ft_initialize_vectors(data, rc);
}