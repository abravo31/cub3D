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

static void	draw_ray(t_cub3D *data, t_rc *rc, t_vec2D ray)
{
	t_vec2D		ray_screen;
	t_vec2D		player_screen;

	player_screen = rc->player.d_coords;
	ray_screen = scalar_mult(ray, rc->scale_map);
	player_screen = scalar_mult(player_screen, rc->scale_map);
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
	printf("Valor antes de la rotacion vector	-> x: %f - y : %f\n", rc->dir_vec.x, rc->dir_vec.y);
	printf("Valor del angulo de rotacion %d\n", rc->angle_direction);
	rc->dir_vec = rotate_2D_vector(rc->dir_vec, rc->angle_direction);
	printf("Valor despues de la rotacion vector	-> x: %f - y : %f\n", rc->dir_vec.x, rc->dir_vec.y);
	// Perpendicular con respecto al vector direccion
	rc->per_vec = ft_get_perpendicular_vec(rc->dir_vec);
	// Vector resultante entre la suma del vector del jugador y el vector direccion
	rc->center_screen = add_2D_vec(rc->player.d_coords, rc->dir_vec);
}

// static void	ft_ray(double ray_angle, int columnXaxis)
// {
// 	t_ray	ray;

// 	// Normalize angle
// 	ray.ray_angle = normalize_angle(ray_angle);
// 	if (ray.ray_angle > 0 && ray.ray_angle < M_PI)
// 		ray.is_facing_up = 1;
// 	else
// 		ray.is_facing_down = 1;
// 	if (ray.ray_angle < (0.5 * M_PI) || ray.ray_angle < (1.5 * M_PI))
// 		ray.is_facing_rigth = 1;
// 	else
// 		ray.is_facing_left = 1;
	
// }

// static void	cast_ray(t_cub3D *data, t_rc *rc, t_vec2D ray_vec)
// {
// 	(void)data;
// 	(void)rc;
// 	if (ray_vec.x > 0)
//     {
//         printf("El rayo está mirando hacia la derecha.\n");
//         // Realizar acciones específicas para la dirección hacia la derecha
//     }
//     else if (ray_vec.x < 0)
//     {
//         printf("El rayo está mirando hacia la izquierda.\n");
//         // Realizar acciones específicas para la dirección hacia la izquierda
//     }

//     if (ray_vec.y > 0)
//     {
//         printf("El rayo está mirando hacia abajo.\n");
//         // Realizar acciones específicas para la dirección hacia abajo
//     }
//     else if (ray_vec.y < 0)
//     {
//         printf("El rayo está mirando hacia arriba.\n");
//         // Realizar acciones específicas para la dirección hacia arriba
//     }

// }

static void	lauch_rays(t_cub3D *data, t_rc *rc)
{
	t_vec2D	cur_pix_pos;
	// t_vec2D	ray_dir;
	t_vec2D	current_ray_dir;
	int		i;

	printf("**************************************************\n");
	printf("angle_redir : %d\n", rc->angle_direction);
	printf("Player vector 	-> x: %f - y : %f\n", rc->player.d_coords.x, rc->player.d_coords.y);
	printf("Dir vector		-> x: %f - y : %f\n", rc->dir_vec.x, rc->dir_vec.y);
	printf("Per_vec 		-> x: %f - y : %f\n", rc->per_vec.x, rc->per_vec.y);
	i = 0;
	while (i <= data->win_x)
	{
		cur_pix_pos = scalar_mult(rc->per_vec, tan(rc->fov / 2) - (rc->ray_dist * i));
		current_ray_dir = add_2D_vec(cur_pix_pos, rc->dir_vec);
		// current_ray_dir = add_2D_vec(current_ray_dir, rc->player.d_coords);
		// ray_dir = subtract_2D_vec(current_ray_dir, rc->player.d_coords);
		if (i == 0 || i == 1200)
		{
			printf("current_ray x %f -- y %f\n", current_ray_dir.x, current_ray_dir.y);
			// printf("cur_pix_pos x %f -- y %f\n", cur_pix_pos.x, cur_pix_pos.y);
			// printf("ray_dir x %f -- y %f\n", ray_dir.x, ray_dir.y);
			// cast_ray(data, rc, current_ray_dir)
			// draw_ray(data, rc, current_ray_dir);
		}
		i++;
	}
}

void    dda(t_cub3D *data)
{
    t_rc	*rc;

	rc = &data->rc;
    get_vectors(rc);
	// lauch_rays(data, rc);
}
