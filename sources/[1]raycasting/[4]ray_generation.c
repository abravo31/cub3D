#include "../../includes/cub3D_struct.h"

static void	initialize_ray(t_ray *ray, t_vec2D ray_vec)
{
	ray->ray_vector = ray_vec;
	ray->hit_point.x = -1;
	ray->hit_point.y = -1;
	ray->distance = -1;
	ray->hit_vertical = -1;
	ray->hit_horizontal = -1;
	ray->orientation_wall_hit = -1;
	ray->is_facing_down = 0;
	ray->is_facing_up = 0;
	ray->is_facing_rigth = 0;
	ray->is_facing_left = 0;
}

// static void	print_ray_info(t_ray *ray)
// {
// 	printf("Distance %f\n", ray->distance);
// 	printf("HitPoint x %f -- y %f\n", ray->hit_point.x, ray->hit_point.y);
// 	printf("Orientation wallhit %d\n", ray->orientation_wall_hit);
// }

static void	get_quadrant(t_ray *ray)
{
	if (!(ft_abs_double(ray->ray_vector.y) < 0.00001))
	{
		if (ray->ray_vector.y < 0)
		{
			ray->is_facing_up = 1;
		}
		else if (ray->ray_vector.y > 0)
		{
			ray->is_facing_down = 1;
		}
	}
	// else
	// {
	// 	// printf("no quadrant defined in up down!\n");
	// 	// ray->is_facing_up = 1;
	// }
	if (!(ft_abs_double(ray->ray_vector.x) < 0.00001))
	{
		if (ray->ray_vector.x < 0)
		{
			ray->is_facing_left = 1;
		}
		else if (ray->ray_vector.x > 0)
		{
			ray->is_facing_rigth = 1;
		}
	}
	// else
	// {
	// 	// printf("no quadrant defined rigth left!\n");
	// 	// ray->is_facing_rigth = 1;
	// }
	// printf("\n\n");
}

static void	cast_ray(t_cub3D *data, t_rc *rc, t_vec2D ray_vec, int i)
{
	t_ray		ray;
	t_vec2D		ray_screen;
	t_vec2D		player_screen;

	player_screen = rc->player.d_coords;
	initialize_ray(&ray, ray_vec);
	get_quadrant(&ray);
	wall_finder(data, &ray, rc, i);
	// print_ray_info(&ray);
	/****************************************************/
	ray_screen = add_2D_vec(player_screen, ray.hit_point);
	ray_screen = scalar_mult(ray.hit_point, rc->scale_map);
	player_screen = scalar_mult(player_screen, rc->scale_map);
	// draw_column(data, &ray, i);
	// draw_scene(data);

	// (void)ray_screen;
	if (ray.orientation_wall_hit >= 1 && ray.orientation_wall_hit <= 4)
		ft_draw_line(data, player_screen, ray_screen, 0xA020F0);
	else if (ray.orientation_wall_hit == 5)
		ft_draw_line(data, player_screen, ray_screen, 0x8B0000);
	else if (ray.orientation_wall_hit == 6)
		ft_draw_line(data, player_screen, ray_screen, 0x606060);
	// ft_draw_line(data, player_screen, ray_screen, 0xA020F0);
	/****************************************************/
}

static void	lauch_rays(t_cub3D *data, t_rc *rc)
{
	t_vec2D	cur_pix_pos;
	t_vec2D	current_ray_dir;
	int		i;

	// printf("**************************************************\n");
	// printf("angle_redir : %d\n", rc->angle_direction);
	// printf("Player vector 	-> x: %f - y : %f\n", rc->player.d_coords.x, rc->player.d_coords.y);
	// printf("Dir vector		-> x: %f - y : %f\n", rc->dir_vec.x, rc->dir_vec.y);
	// printf("Per_vec 		-> x: %f - y : %f\n", rc->per_vec.x, rc->per_vec.y);
	i = 0;
	while (i <= data->win_x)
	{
		cur_pix_pos = scalar_mult(rc->per_vec, tan(rc->fov * 0.5) - (rc->ray_dist * i));
		current_ray_dir = add_2D_vec(cur_pix_pos, rc->dir_vec);
		normalize_vector(&current_ray_dir);
		// if (i == 0 || i == data->win_x)
		// {
		// 	cast_ray(data, rc, current_ray_dir, i);
		// }
		// if (i % 50 == 0)
		// {
		// 	cast_ray(data, rc, current_ray_dir, i);
		// }
		cast_ray(data, rc, current_ray_dir, i);
		i++;
	}
	// draw_scene(data);
}

void    raycasting(t_cub3D *data)
{
    t_rc	*rc;

	rc = &data->rc;
   	// Perpendicular con respecto al vector direccion
	rc->per_vec = ft_get_perpendicular_vec(rc->dir_vec);
	// Vector resultante entre la suma del vector del jugador y el vector direccion
	rc->center_screen = add_2D_vec(rc->player.d_coords, rc->dir_vec);
	_raycasting(data);
	// draw_scene(data);
	lauch_rays(data, rc);
}
