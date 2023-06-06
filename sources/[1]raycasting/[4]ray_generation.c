#include "../../includes/cub3D_struct.h"

static void	initialize_ray(t_ray *ray, t_vec2D ray_vec, int doors)
{
	if (doors == 1)
		ray->ray_type = 1;
	else
		ray->ray_type = 2;
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
}

static void	cast_ray(t_cub3D *data, t_rc *rc, t_vec2D ray_vec, int i)
{
	t_ray		ray;
	t_vec2D		ray_screen;
	t_vec2D		player_screen;

	player_screen = rc->player.d_coords;
	initialize_ray(&ray, ray_vec, 0);
	get_quadrant(&ray);
	// printf("Soy rayo\n");
	wall_finder(data, &ray, rc, i);
	// print_ray_info(&ray);
	/****************************************************/
	ray_screen = add_2D_vec(player_screen, ray.hit_point);
	ray_screen = scalar_mult(ray.hit_point, rc->scale_map);
	player_screen = scalar_mult(player_screen, rc->scale_map);
	// printf("orientation wall hit %d\n", ray.orientation_wall_hit);
	draw_column(data, &ray, i);
	// draw_scene(data);

	// // (void)ray_screen;
	// if (ray.orientation_wall_hit >= 1 && ray.orientation_wall_hit <= 4)
	// 	ft_draw_line(data, player_screen, ray_screen, 0xA020F0);
	// else if (ray.orientation_wall_hit == 5)
	// 	ft_draw_line(data, player_screen, ray_screen, 0x8B0000);
	// else if (ray.orientation_wall_hit == 6)
	// 	ft_draw_line(data, player_screen, ray_screen, 0x606060);
	// ft_draw_line(data, player_screen, ray_screen, 0xA020F0);
	/****************************************************/
}

static void	lauch_rays(t_cub3D *data, t_rc *rc)
{
	t_vec2D	cur_pix_pos;
	t_vec2D	current_ray_dir;
	int		i;

	i = 0;
	while (i <= data->win_x)
	{
		cur_pix_pos = scalar_mult(rc->per_vec, tan(rc->fov * 0.5) - (rc->ray_dist * i));
		current_ray_dir = add_2D_vec(cur_pix_pos, rc->dir_vec);
		normalize_vector(&current_ray_dir);
		// if (i == 0 || i == (data->win_x / 2) || i == data->win_x)
		// 	cast_ray(data, rc, current_ray_dir, i);
		// if (i == (data->win_x / 2))
		// 	cast_ray(data, rc, current_ray_dir, i);
		// if (i == 0)
		// 	cast_ray(data, rc, current_ray_dir, i);
		// if (i == data->win_x)
		// 	cast_ray(data, rc, current_ray_dir, i);
		cast_ray(data, rc, current_ray_dir, i);
		i++;
	}
}

static void	check_door_hook(t_rc *rc, t_door *door)
{
	if (rc->doors)
	{
		if ((*door->status) == CLOSED)
		{
			(*door->status) = OPENING;
		}
		else if ((*door->status) == OPEN)
		{
			(*door->status) = CLOSING;
		}
	}
	rc->doors = 0;
}

static void	check_distance_door(t_cub3D *data, t_rc *rc, t_ray *ray, t_door *door)
{
	if (door->type_door == VERTICAL_DOOR)
	{
		if (ray->is_facing_rigth)
		{
			if (rc->center_screen.x >= (door->initial_dda.x + 0.5))
			{
				printf("Here I can open the door in the rigth\n");
				printf("Value of hook for doors %d\n", rc->doors);
				check_door_hook(rc, door);
			}
		}
		else if (ray->is_facing_left)
		{
			if (rc->center_screen.x <= (door->initial_dda.x + 0.5))
			{
				printf("Here I can open the door in the left\n");
				printf("Value of hook for doors %d\n", rc->doors);
				check_door_hook(rc, door);
			}
		}
	}
	else if (door->type_door == HORIZONTAL_DOOR)
	{
		if (ray->is_facing_up)
		{
			if (rc->center_screen.y <= (door->initial_dda.y + 0.5))
			{
				printf("Here I can open the door in the up\n");
				printf("Value of hook for doors %d\n", rc->doors);
				check_door_hook(rc, door);
			}
		}
		else if (ray->is_facing_down)
		{
			if (rc->center_screen.y >= (door->initial_dda.y + 0.5))
			{
				printf("Here I can open the door in the down\n");
				printf("Value of hook for doors %d\n", rc->doors);
				check_door_hook(rc, door);
			}
		}
	}
}

// static void	raycasting_door
static void	lauch_door_ray(t_cub3D *data, t_rc *rc)
{
	t_ray		ray;
	int			i;

	initialize_ray(&ray, rc->dir_vec, 1);
	get_quadrant(&ray);
	wall_finder(data, &ray, rc, 0);
	// printf("hit point x %f | y %f\n", ray.hit_point.x, ray.hit_point.y);
	draw_square_point(data, ray.hit_point);
	// printf("orientation hit of dir vector %d\n", ray.orientation_wall_hit);
	// printf("index of the elem %d %d \n", (int)ray.hit_point.y, (int)ray.hit_point.x);
	if (data->door.status != NULL)
	{
		// printf("here is status %d\n", (*data->door.status));
		check_distance_door(data, rc, &ray, &data->door);
		if ((*data->door.status) == OPENING)
		{
			printf("Suelta el timer opening\n");
			i = 0;
			while ((*data->door.timer) < 1.0)
			{
				// printf("******** one iteration %d *******\n", i);
				lauch_rays(data, rc);
				(*data->door.timer) = (*data->door.timer) + 0.05;
				i++;
			}
			printf("Para el timer opening\n");
			(*data->door.status) = OPEN;
		}
		else if ((*data->door.status) == CLOSING)
		{
			// printf("Suelta el timer closing\n");
			while ((*data->door.timer) > 0.0)
			{
				lauch_rays(data, rc);
				(*data->door.timer) = (*data->door.timer) - 0.05;
			}
			(*data->door.status) = CLOSED;
		}
	}
}

void    raycasting(t_cub3D *data)
{
    t_rc	*rc;

	rc = &data->rc;
   	// Perpendicular con respecto al vector direccion
	rc->per_vec = ft_get_perpendicular_vec(rc->dir_vec);
	// Vector resultante entre la suma del vector del jugador y el vector direccion
	rc->center_screen = add_2D_vec(rc->player.d_coords, rc->dir_vec);	
	// printf("status of door %d\n", (*data->door.status));
	// _raycasting(data);
	draw_square_point(data, data->rc.center_screen);
	// cast_ray(data, rc, rc->dir_vec, 0);
	lauch_door_ray(data, rc);
	// printf("status %d\n", (*data->door.status));
	// draw_scene(data);
	// check_distance_door(data, rc, )
	lauch_rays(data, rc);
}
