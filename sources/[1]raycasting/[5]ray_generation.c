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

static void	initialize_ray(t_rc *rc, t_ray *ray, t_vec2D ray_vec)
{
	double left_or_rigth;

	ray->ray_vector = ray_vec;
	ray->hit_point.x = -1;
	ray->hit_point.y = -1;
	ray->distance = -1;
	ray->orientation_wall_hit = -1;
	ray->is_facing_down = 0;
	ray->is_facing_up = 0;
	ray->is_facing_rigth = 0;
	ray->is_facing_left = 0;
}

static void	get_int_coords(t_player *player)
{
	double		integer_value;
	double		double_value;

	double_value = modf(player->d_coords.x, &integer_value);
	player->i_coords.x = (int)integer_value;
	double_value = modf(player->d_coords.y, &integer_value);
	player->i_coords.y = (int)integer_value;
}

static void	get_quadrant(t_ray *ray)
{
	if (ray->ray_vector.y < 0)
	{
		ray->is_facing_up = 1;
		printf("El rayo esta mirando para arriba");
	}
	else if (ray->ray_vector.y > 0)
	{
		ray->is_facing_down = 1;
		printf("El rayo esta mirando para abajo");
	}
    if (ray->ray_vector.x < 0)
	{
		ray->is_facing_left = 1;
		printf(" y para la izquierda");
	}
    else if (ray->ray_vector.x > 0)
	{
		ray->is_facing_rigth = 1;
		printf(" y para la derecha");
	}
	printf("\n");
}

static int	hit_wall(int **map, t_vec2D current_dda, int *orientation_wall_hit)
{
	if (*orientation_wall_hit == 1)
	{
		if (map[(int)current_dda.y - 1][(int)current_dda.x] == 1)
			return (1);
		current_dda.y = current_dda.y - 1;
	}
	else if (*orientation_wall_hit == 2)
	{
		if (map[(int)current_dda.y + 1][(int)current_dda.x] == 1)
			return (1);
		current_dda.y = current_dda.y + 1;
	}
	else if (*orientation_wall_hit == 3)
	{
		if (map[(int)current_dda.y][(int)current_dda.x + 1] == 1)
			return (1);
		current_dda.x = current_dda.x + 1;
	}
	else if (*orientation_wall_hit == 4)
	{
		if (map[(int)current_dda.y][(int)current_dda.x - 1] == 1)
			return (1);
		current_dda.x = current_dda.x - 1;
	}
	*orientation_wall_hit = -1;
	return (0);
}

static void	wall_finder(t_cub3D *data, t_ray *ray, t_rc *rc)
{
	t_vec2D	current_dda;

	get_int_coords(&data->rc.player);
	current_dda.x = rc->player.i_coords.x;
	current_dda.y = rc->player.i_coords.y;
	// printf("Pos int player x %d - y %d\n", current_dda.x, current_dda.y);
	printf("current_dda x %f - y %f\n", current_dda.x, current_dda.y);
	// printf("up %d\n", ray->is_facing_up);
	// printf("down %d\n", ray->is_facing_down);
	// printf("rigth %d\n", ray->is_facing_rigth);
	// printf("left %d\n", ray->is_facing_left);

	while (hit_wall(data->map.map, current_dda, &ray->orientation_wall_hit) == 0)
	{
		if (ray->is_facing_up == 1 && ray->orientation_wall_hit == -1)
		{
			// Es para evitar que la division entre 0
			if (!(ft_abs_double(ray->ray_vector.y) < 0.00001))
			{
				ray->distance = (current_dda.y - rc->player.d_coords.y ) / ray->ray_vector.y;
				ray->hit_point.x = rc->player.d_coords.x + (ray->distance * ray->ray_vector.x);
				ray->hit_point.y = current_dda.y;
				// En este caso tocamos el muro en sentido norte y no esta dentro del rango de nuestro jugador
				if (ray->hit_point.x > current_dda.x && ray->hit_point.x < (current_dda.x + 1))
					ray->orientation_wall_hit = 1;
			}
		}
		else if (ray->is_facing_down == 1 && ray->orientation_wall_hit == -1)
		{
			if (!(ft_abs_double(ray->ray_vector.y) < 0.00001))
			{
				ray->distance = ((current_dda.y + 1) - rc->player.d_coords.y ) / ray->ray_vector.y;
				ray->hit_point.x = rc->player.d_coords.x + (ray->distance * ray->ray_vector.x);
				ray->hit_point.y = current_dda.y + 1;
				// En este caso tocamos el muro en sentido norte y no esta dentro del rango de nuestro jugador
				if (ray->hit_point.x > current_dda.x && ray->hit_point.x < (current_dda.x + 1))
					ray->orientation_wall_hit = 2;
			}
		}
		if  (ray->is_facing_left == 1 && ray->orientation_wall_hit == -1)
		{
			printf("Left\n");
			if (!(ft_abs_double(ray->ray_vector.x) < 0.00001))
			{
				ray->distance = ((current_dda.x) - rc->player.d_coords.x) / ray->ray_vector.x;
				ray->hit_point.x = current_dda.x;
				ray->hit_point.y = rc->player.d_coords.y + (ray->distance * ray->ray_vector.y);
				ray->orientation_wall_hit = 4;
				printf("ray distance %f \n", ray->distance);
				printf("ray hit_poirnt x %f \n", ray->hit_point.x);
				printf("ray hit ppoint y  %f \n", ray->hit_point.y);
				printf("ray orent %d \n", ray->orientation_wall_hit);
			}
			else
				printf("Bloqueado\n");
		}
		else if (ray->is_facing_rigth == 1 && ray->orientation_wall_hit == -1)
		{
			printf("Rigth\n");
			// // En este caso tocamos el muro en sentido este y no esta dentro del rango de nuestro jugador
			if (!(ft_abs_double(ray->ray_vector.x) < 0.00001))
			{
				ray->distance = ((current_dda.x + 1) - rc->player.d_coords.x) / ray->ray_vector.x;
				ray->hit_point.x = current_dda.x + 1;
				ray->hit_point.y = rc->player.d_coords.y + (ray->distance * ray->ray_vector.y);
				ray->orientation_wall_hit = 3;
				printf("ray distance %f \n", ray->distance);
				printf("ray hit_poirnt x %f \n", ray->hit_point.x);
				printf("ray hit ppoint y  %f \n", ray->hit_point.y);
				printf("ray orent %d \n", ray->orientation_wall_hit);
			}
			else
				printf("Bloqueado\n");
		}
	}
	printf("distance : %f\n", ray->distance);
	draw_square_point(data, ray->hit_point);
}

static void	cast_ray(t_cub3D *data, t_rc *rc, t_vec2D ray_vec)
{
	t_ray		ray;
	t_vec2D		ray_screen;
	t_vec2D		player_screen;

	player_screen = rc->player.d_coords;
	ray_screen = add_2D_vec(player_screen, ray_vec);
	ray_screen = scalar_mult(ray_screen, rc->scale_map);
	player_screen = scalar_mult(player_screen, rc->scale_map);
	initialize_ray(rc, &ray, ray_vec);
	get_quadrant(&ray);
	wall_finder(data, &ray, rc);
	draw_square(data, (int)ray_screen.y, (int)ray_screen.x, 3, 5);
	ft_draw_line(data, player_screen, ray_screen, 0xA020F0);
}

static void get_vectors(t_rc *rc)
{
	// printf("Valor del rotacion vector	-> x: %f - y : %f\n", rc->dir_vec.x, rc->dir_vec.y);
	// Perpendicular con respecto al vector direccion
	rc->per_vec = ft_get_perpendicular_vec(rc->dir_vec);
	// printf("Valor del  per vector	-> x: %f - y : %f\n", rc->per_vec.x, rc->per_vec.y);
	// Vector resultante entre la suma del vector del jugador y el vector direccion
	rc->center_screen = add_2D_vec(rc->player.d_coords, rc->dir_vec);
	// printf("Valor del center_screen -> x: %f - y : %f\n", rc->center_screen.x, rc->center_screen.y);
}

static void	lauch_rays(t_cub3D *data, t_rc *rc)
{
	t_vec2D	cur_pix_pos;
	// t_vec2D	ray_dir;
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
		cur_pix_pos = scalar_mult(rc->per_vec, tan(rc->fov / 2) - (rc->ray_dist * i));
		current_ray_dir = add_2D_vec(cur_pix_pos, rc->dir_vec);
		// printf("current_ray x %f -- y %f\n", current_ray_dir.x, current_ray_dir.y);
		normalizeVector(&current_ray_dir);
		if (i == data->win_x)
		{
			// printf("current_ray normalized x %f -- y %f\n", current_ray_dir.x, current_ray_dir.y);
			cast_ray(data, rc, current_ray_dir);
		}
		i++;
	}
}

void    dda(t_cub3D *data)
{
    t_rc	*rc;

	rc = &data->rc;
    get_vectors(rc);
	draw_scene(data);
	lauch_rays(data, rc);
}
