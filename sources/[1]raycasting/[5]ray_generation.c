#include "../../includes/cub3D_struct.h"

t_vec2D ft_get_perpendicular_vec(t_vec2D dir_vec)
{
    t_vec2D res_perpendicular_vec;
    double norm;

	res_perpendicular_vec.x = 0;
	res_perpendicular_vec.y = 0;
    if (dir_vec.y != 0)
    {
		if (dir_vec.y < 0)
		{
			 norm = sqrt(1 + ((dir_vec.x * dir_vec.x) / (dir_vec.y * dir_vec.y)));
			res_perpendicular_vec.x = -1 / norm;
			res_perpendicular_vec.y = (dir_vec.x / dir_vec.y) / norm;
		}
		else if (dir_vec.y > 0)
		{
			norm = sqrt(1 + ((dir_vec.x * dir_vec.x) / (dir_vec.y * dir_vec.y)));
        	res_perpendicular_vec.x = 1 / norm;
        	res_perpendicular_vec.y = -(dir_vec.x / dir_vec.y) / norm;
		}
    }
    else
    {
		if (dir_vec.x > 0)
		{
			res_perpendicular_vec.x = 0;
        	res_perpendicular_vec.y = -1;
		}
		else if (dir_vec.x < 0)
		{
			res_perpendicular_vec.x = 0;
        	res_perpendicular_vec.y = 1;
		}
    }
    return res_perpendicular_vec;
}

// norm = sqrt(1 + ((dir_vec.y * dir_vec.y) / (dir_vec.x * dir_vec.x)));
// res_perpendicular_vec.x = -(dir_vec.y / dir_vec.x) / norm;
// res_perpendicular_vec.y = 1 / norm;

// t_vec2D	ft_get_perpendicular_vec(t_vec2D dir_vec)
// {
// 	t_vec2D	res_perpendicular_vec;
// 	double	norm;

// 	norm = sqrt(1 + (((dir_vec.x * dir_vec.x) / (dir_vec.y * dir_vec.y))));
// 	res_perpendicular_vec.x = -1 / norm;
// 	res_perpendicular_vec.y = ((dir_vec.x) / dir_vec.y) / norm;
// 	printf("perpendicular x %f - y %f\n", res_perpendicular_vec.x, res_perpendicular_vec.y);
// 	return (res_perpendicular_vec);
// }

static void	draw_ray(t_cub3D *data, t_rc *rc, t_vec2D ray)
{
	t_vec2D		ray_screen;
	t_vec2D		player_screen;

	player_screen = rc->player.d_coords;
	ray_screen = scalar_mult(ray, rc->scale);
	player_screen = scalar_mult(player_screen, rc->scale);
	ft_draw_line(data, player_screen, ray_screen, 0xA020F0);
}

// static void	draw_ray(t_cub3D *data, t_rc *rc, t_vec2D ray)
// {
// 	(void)data;
// 	// t_vec2D		ray_screen;
// 	t_vec2D		player_screen;
// 	// t_vec2D		vec_limit;
// 	// t_vec2D		end_vector;

// 	player_screen = rc->player.d_coords;
// 	printf("player y %f -- x %f\n", player_screen.y, player_screen.x);
// 	printf("ray y %f -- x %f\n", ray.y, ray.x);
// }

static void get_vectors(t_rc *rc)
{
    rc->dir_vec = rotate_2D_vector(rc->initial_dir_vec, rc->angle_direction);
	rc->plane_vec = ft_get_perpendicular_vec(rc->dir_vec);
	rc->player_dir_vec = add_2D_vec(rc->player.d_coords, rc->dir_vec);
}

static void	lauch_rays(t_cub3D *data, t_rc *rc)
{
	t_vec2D	pos_plane_vec;
	t_vec2D	current_ray_dir;
	// t_vec2D	current_ray;
	int		i;

	printf("Player vector 	-> y: %f - x : %f\n", rc->player.d_coords.y, rc->player.d_coords.x);
	printf("Dir vector		-> y: %f - x : %f\n", rc->dir_vec.y, rc->dir_vec.x);
	printf("Plane_vec 		-> y: %f - x : %f\n", rc->plane_vec.y, rc->plane_vec.x);
	i = 0;
	while (i <= data->win_x)
	{
		pos_plane_vec = scalar_mult(rc->plane_vec, tan(rc->fov / 2) - (rc->ray_dist * i));
		// printf("pos_plane_vec x %f -- y %f\n", pos_plane_vec.x, pos_plane_vec.y);
		current_ray_dir = add_2D_vec(pos_plane_vec, rc->player_dir_vec);
		// current_ray = add_2D_vec(current_ray_dir, rc->player.d_coords);
		// printf("current_ray_dir x %f -- y %f\n", current_ray_dir.x, current_ray_dir.y);
		// printf("pos player x %f -- y %f\n", rc->player.d_coords.x, rc->player.d_coords.y);
		// draw_ray(data, rc, current_ray_dir);
		if (i % 100 == 0)
		{
			printf("current_ray x %f -- y %f\n", current_ray_dir.x, current_ray_dir.y);
			// double deltaDistX = (current_ray_dir.x == 0) ? 1e30 : fabs(1 / current_ray_dir.x);
      		// double deltaDistY = (current_ray_dir.y == 0) ? 1e30 : fabs(1 / current_ray_dir.y);
			// printf("deltaDistX %f -- deltaDistY %f\n", deltaDistX, deltaDistY);
			draw_ray(data, rc, current_ray_dir);
			// printf("%d\n", i);
		}
		i++;
	}
}

void    dda(t_cub3D *data)
{
    t_rc	*rc;

	rc = &data->rc;
    get_vectors(rc);
	lauch_rays(data, rc);
}
