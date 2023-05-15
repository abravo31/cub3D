#include "../../includes/cub3D_struct.h"

static void	get_int_coords(t_player *player)
{
	double		integer_value;
	double		double_value;

	double_value = modf(player->d_coords.x, &integer_value);
	player->i_coords.x = (int)integer_value;
	double_value = modf(player->d_coords.y, &integer_value);
	player->i_coords.y = (int)integer_value;
    (void)double_value;
}

static int	hit_wall(int **map, t_vec2D *current_dda, int *orientation_wall_hit)
{
	if (*orientation_wall_hit == 1)
	{
		if (map[(int)current_dda->y - 1][(int)current_dda->x] == 1)
		{
			printf("Position of the map that was checked y %d -- x %d\n", (int)current_dda->y - 1, (int)current_dda->x);
			return (1);
		}
		current_dda->y = current_dda->y - 1;
	}
	else if (*orientation_wall_hit == 2)
	{
		if (map[(int)current_dda->y + 1][(int)current_dda->x] == 1)
		{
			printf("Position of the map that was checked y %d -- x %d\n", (int)current_dda->y + 1, (int)current_dda->x);
			return (1);
		}
		current_dda->y = current_dda->y + 1;
	}
	else if (*orientation_wall_hit == 3)
	{
		if (map[(int)current_dda->y][(int)current_dda->x + 1] == 1)
		{
			printf("here Position of the map that was checked y %d -- x %d\n", (int)current_dda->y, (int)current_dda->x + 1);
			return (1);
		}
		current_dda->x = current_dda->x + 1;
	}
	else if (*orientation_wall_hit == 4)
	{
		if (map[(int)current_dda->y][(int)current_dda->x - 1] == 1)
		{
			printf("Position of the map that was checked y %d -- x %d\n", (int)current_dda->y, (int)current_dda->x - 1);
			return (1);
		}
		current_dda->x = current_dda->x - 1;
	}
	*orientation_wall_hit = -1;
	return (0);
}

/******************************************************
This function is only for draw the rays in the screen
*******************************************************/
static void	draw_ray(t_cub3D *data, t_rc *rc, t_vec2D ray_hit_point)
{
	t_vec2D		ray_hit_point_screen;
	t_vec2D		player_screen;

	player_screen = rc->player.d_coords;
	ray_hit_point_screen = scalar_mult(ray_hit_point, rc->scale_map);
	player_screen = scalar_mult(player_screen, rc->scale_map);
	ft_draw_line(data, player_screen, ray_hit_point_screen, 0xA020F0);
}

// static void	check_hit_X_axis()
// {

// }

static void	check_hit_Y_axis(t_cub3D *data, t_rc *rc, t_ray *ray, t_vec2D *current_dda)
{
	printf("ray_vector x : %f -- y : %f\n", ray->ray_vector.x, ray->ray_vector.y);
	printf("current dda x : %f -- y : %f\n", current_dda->x, current_dda->y);
	if (ray->is_facing_up == 1 && ray->orientation_wall_hit == -1)
	{
		// Es para evitar que la division entre 0
		printf("Up\n");
		if (!(ft_abs_double(ray->ray_vector.y) < 0.00001))
		{
			ray->distanceY = (current_dda->y - rc->player.d_coords.y) / ray->ray_vector.y;
			printf("Hereee %f\n", ray->distanceY);
			ray->hit_pointY.x = rc->player.d_coords.x + (ray->distanceY * ray->ray_vector.x);
			ray->hit_pointY.y = current_dda->y;
		}
	}
	else if (ray->is_facing_down == 1 && ray->orientation_wall_hit == -1)
	{
		printf("Down\n");
		if (!(ft_abs_double(ray->ray_vector.y) < 0.00001))
		{
			ray->distanceY = ((current_dda->y + 1) - rc->player.d_coords.y) / ray->ray_vector.y;
			ray->hit_pointY.x = rc->player.d_coords.x + (ray->distanceY * ray->ray_vector.x);
			ray->hit_pointY.y = current_dda->y + 1;
			// En este caso tocamos el muro en sentido sur yesta dentro del rango de nuestro jugador
			if (ray->hit_pointY.x > current_dda->x && ray->hit_pointY.x < (current_dda->x + 1))
			{
				ray->orientation_wall_hit = 2;
			}
		}
	}
	draw_square_point(data, ray->hit_pointY);
}

static void	check_hit_X_axis(t_cub3D *data, t_rc *rc, t_ray *ray, t_vec2D *current_dda)
{
	// printf("ray_vector x : %f -- y : %f\n", ray->ray_vector.x, ray->ray_vector.y);
	// printf("current dda x : %f -- y : %f\n", current_dda->x, current_dda->y);
	if  (ray->is_facing_left == 1 && ray->orientation_wall_hit == -1)
	{
		printf("Left\n");
		if (!(ft_abs_double(ray->ray_vector.x) < 0.00001))
		{
			ray->distanceX = ((current_dda->x) - rc->player.d_coords.x) / ray->ray_vector.x;
			ray->hit_pointX.x = current_dda->x;
			ray->hit_pointX.y = rc->player.d_coords.y + (ray->distanceX * ray->ray_vector.y);
			ray->orientation_wall_hit = 4;
			// printf("Hit point x %f - y %f\n", ray->hit_point.x, ray->hit_point.y);
			// printf("ray distance : %f\n", ray->distance);
			// draw_square_point(data, ray->hit_point);
			// hit = hit_wall(data->map.map, &current_dda, &ray->orientation_wall_hit);
		}
	}
	else if (ray->is_facing_rigth == 1 && ray->orientation_wall_hit == -1)
	{
		printf("Rigth\n");
		// // En este caso tocamos el muro en sentido este y no esta dentro del rango de nuestro jugador
		if (!(ft_abs_double(ray->ray_vector.x) < 0.00001))
		{
			ray->distanceX = ((current_dda->x + 1) - rc->player.d_coords.x) / ray->ray_vector.x;
			ray->hit_pointX.x = current_dda->x + 1;
			ray->hit_pointX.y = rc->player.d_coords.y + (ray->distanceX * ray->ray_vector.y);
			ray->orientation_wall_hit = 3;
			// printf("Hit point x %f - y %f\n", ray->hit_point.x, ray->hit_point.y);
			// printf("ray distance : %f\n", ray->distance);
			// draw_square_point(data, ray->hit_point);
			// hit = hit_wall(data->map.map, &current_dda, &ray->orientation_wall_hit);
			// printf("Here Hit point x %f - y %f\n", ray->hit_point.x, ray->hit_point.y);
		}
	}
	draw_square_point(data, ray->hit_pointX);
}


void	wall_finder(t_cub3D *data, t_ray *ray, t_rc *rc)
{
	t_vec2D	current_dda;
	int		hit;


	get_int_coords(&data->rc.player);
	current_dda.x = rc->player.i_coords.x;
	current_dda.y = rc->player.i_coords.y;
	printf("Pos int player at the beginning x %f - y %f\n", current_dda.x, current_dda.y);
	// printf("current_dda x %f - y %f\n", current_dda.x, current_dda.y);
	// printf("up %d\n", ray->is_facing_up);
	// printf("down %d\n", ray->is_facing_down);
	// printf("rigth %d\n", ray->is_facing_rigth);
	// printf("left %d\n", ray->is_facing_left);

	hit = 0;
	while (!hit)
	{
		printf("Check %f - y %f\n", current_dda.x, current_dda.y);
		check_hit_Y_axis(data, rc, ray, &current_dda);
		check_hit_X_axis(data, rc, ray, &current_dda);
		if (ray->distanceX < ray->distanceY)
		{
			// printf("Distance en X es %f menor que %f\n", ray->distanceX, ray->distanceY);
			current_dda.y = current_dda.x + 1;
			ray->orientation_wall_hit = -1;
		}
		else
		{
			// printf("else\n");
			current_dda.y = current_dda.y - 1;
			ray->orientation_wall_hit = -1;
		}
		if (data->map.map[(int)current_dda.y][(int)current_dda.x] == 1)
			hit = 1;
	}
	printf("Here!\n");
	// if (ray->distanceX < ray->distanceY)
	// {
	// 	printf("Distance en X es %f menor que %f\n", ray->distanceX, ray->distanceY);
	// 	current_dda.y = current_dda.x + 1;
	// 	ray->orientation_wall_hit = -1;
	// }
	// else
	// {
	// 	printf("else\n");
	// 	current_dda.y = current_dda.y - 1;
	// 	ray->orientation_wall_hit = -1;
	// }
	// printf("***************************************\n");
	// check_hit_Y_axis(data, rc, ray, &current_dda);
	// check_hit_X_axis(data, rc, ray, &current_dda);
	// while (hit_wall(data->map.map, current_dda, &ray->orientation_wall_hit) == 0)
	// while (!hit)
	// {

	// }
	// while (!hit)
	// {
	// 	printf("ray vector x %f - y %f\n", ray->ray_vector.x, ray->ray_vector.y);
	// 	if (ray->is_facing_up == 1 && ray->orientation_wall_hit == -1)
	// 	{
	// 		// Es para evitar que la division entre 0
	// 		printf("Up\n");
	// 		if (!(ft_abs_double(ray->ray_vector.y) < 0.00001))
	// 		{
	// 			ray->distance = (current_dda.y - rc->player.d_coords.y) / ray->ray_vector.y;
	// 			ray->hit_point.x = rc->player.d_coords.x + (ray->distance * ray->ray_vector.x);
	// 			ray->hit_point.y = current_dda.y;
	// 			// En este caso tocamos el muro en sentido norte y esta dentro del rango de nuestro jugador
	// 			if (ray->hit_point.x > current_dda.x && ray->hit_point.x < (current_dda.x + 1))
	// 			{
	// 				// printf("current_dda x %f - y %f\n", current_dda.x, current_dda.y);
	// 				// printf("hit point x %f - y %f\n", ray->hit_point.x, ray->hit_point.y);
	// 				ray->orientation_wall_hit = 1;
	// 				printf("Hit point x %f - y %f\n", ray->hit_point.x, ray->hit_point.y);
	// 				printf("ray distance : %f\n", ray->distance);
	// 				draw_square_point(data, ray->hit_point);
	// 				hit = hit_wall(data->map.map, &current_dda, &ray->orientation_wall_hit);
	// 			}
	// 		}
	// 	}
	// 	else if (ray->is_facing_down == 1 && ray->orientation_wall_hit == -1)
	// 	{
	// 		if (!(ft_abs_double(ray->ray_vector.y) < 0.00001))
	// 		{
	// 			ray->distance = ((current_dda.y + 1) - rc->player.d_coords.y) / ray->ray_vector.y;
	// 			ray->hit_point.x = rc->player.d_coords.x + (ray->distance * ray->ray_vector.x);
	// 			ray->hit_point.y = current_dda.y + 1;
	// 			// En este caso tocamos el muro en sentido sur yesta dentro del rango de nuestro jugador
	// 			if (ray->hit_point.x > current_dda.x && ray->hit_point.x < (current_dda.x + 1))
	// 			{
	// 				ray->orientation_wall_hit = 2;
	// 				printf("Hit point x %f - y %f\n", ray->hit_point.x, ray->hit_point.y);
	// 				printf("ray distance : %f\n", ray->distance);
	// 				draw_square_point(data, ray->hit_point);
	// 				hit = hit_wall(data->map.map, &current_dda, &ray->orientation_wall_hit);
	// 			}
	// 		}
	// 	}
	// 	if  (ray->is_facing_left == 1 && ray->orientation_wall_hit == -1)
	// 	{
	// 		printf("Left\n");
	// 		if (!(ft_abs_double(ray->ray_vector.x) < 0.00001))
	// 		{
	// 			ray->distance = ((current_dda.x) - rc->player.d_coords.x) / ray->ray_vector.x;
	// 			ray->hit_point.x = current_dda.x;
	// 			ray->hit_point.y = rc->player.d_coords.y + (ray->distance * ray->ray_vector.y);
	// 			ray->orientation_wall_hit = 4;
	// 			printf("Hit point x %f - y %f\n", ray->hit_point.x, ray->hit_point.y);
	// 			printf("ray distance : %f\n", ray->distance);
	// 			draw_square_point(data, ray->hit_point);
	// 			hit = hit_wall(data->map.map, &current_dda, &ray->orientation_wall_hit);
	// 		}
	// 	}
	// 	else if (ray->is_facing_rigth == 1 && ray->orientation_wall_hit == -1)
	// 	{
	// 		printf("Rigth\n");
	// 		// // En este caso tocamos el muro en sentido este y no esta dentro del rango de nuestro jugador
	// 		if (!(ft_abs_double(ray->ray_vector.x) < 0.00001))
	// 		{
	// 			ray->distance = ((current_dda.x + 1) - rc->player.d_coords.x) / ray->ray_vector.x;
	// 			ray->hit_point.x = current_dda.x + 1;
	// 			ray->hit_point.y = rc->player.d_coords.y + (ray->distance * ray->ray_vector.y);
	// 			ray->orientation_wall_hit = 3;
	// 			printf("Hit point x %f - y %f\n", ray->hit_point.x, ray->hit_point.y);
	// 			printf("ray distance : %f\n", ray->distance);
	// 			draw_square_point(data, ray->hit_point);
	// 			hit = hit_wall(data->map.map, &current_dda, &ray->orientation_wall_hit);
	// 			// printf("Here Hit point x %f - y %f\n", ray->hit_point.x, ray->hit_point.y);
	// 		}
	// 	}
	// }
	// printf("Here\n");
	// draw_square_point(data, ray->hit_point);
	// draw_ray(data, rc, ray->hit_point);
	// printf("Pego!\n");
	// 	if (ray->is_facing_up == 1 && ray->orientation_wall_hit == -1)
	// 	{
	// 		// Es para evitar que la division entre 0
	// 		if (!(ft_abs_double(ray->ray_vector.y) < 0.00001))
	// 		{
	// 			ray->distance = (current_dda.y - rc->player.d_coords.y ) / ray->ray_vector.y;
	// 			ray->hit_point.x = rc->player.d_coords.x + (ray->distance * ray->ray_vector.x);
	// 			ray->hit_point.y = current_dda.y;
	// 			// En este caso tocamos el muro en sentido norte y esta dentro del rango de nuestro jugador
	// 			if (ray->hit_point.x > current_dda.x && ray->hit_point.x < (current_dda.x + 1))
	// 			{
	// 				printf("Here\n");
	// 				printf("current_dda x %f - y %f\n", current_dda.x, current_dda.y);
	// 				printf("hit point x %f - y %f\n", ray->hit_point.x, ray->hit_point.y);
	// 				ray->orientation_wall_hit = 1;
	// 				printf("hit wall %d\n", hit_wall(data->map.map, &current_dda, &ray->orientation_wall_hit));
	// 			}
	// 		}
	// 	}
	// 	else if (ray->is_facing_down == 1 && ray->orientation_wall_hit == -1)
	// 	{
	// 		if (!(ft_abs_double(ray->ray_vector.y) < 0.00001))
	// 		{
	// 			ray->distance = ((current_dda.y + 1) - rc->player.d_coords.y ) / ray->ray_vector.y;
	// 			ray->hit_point.x = rc->player.d_coords.x + (ray->distance * ray->ray_vector.x);
	// 			ray->hit_point.y = current_dda.y + 1;
	// 			// En este caso tocamos el muro en sentido norte y no esta dentro del rango de nuestro jugador
	// 			if (ray->hit_point.x > current_dda.x && ray->hit_point.x < (current_dda.x + 1))
	// 				ray->orientation_wall_hit = 2;
	// 		}
	// 	}
	// 	if  (ray->is_facing_left == 1 && ray->orientation_wall_hit == -1)
	// 	{
	// 		printf("Left\n");
	// 		if (!(ft_abs_double(ray->ray_vector.x) < 0.00001))
	// 		{
	// 			ray->distance = ((current_dda.x) - rc->player.d_coords.x) / ray->ray_vector.x;
	// 			ray->hit_point.x = current_dda.x;
	// 			ray->hit_point.y = rc->player.d_coords.y + (ray->distance * ray->ray_vector.y);
	// 			ray->orientation_wall_hit = 4;
	// 			printf("ray distance %f \n", ray->distance);
	// 			printf("ray hit_poirnt x %f \n", ray->hit_point.x);
	// 			printf("ray hit ppoint y  %f \n", ray->hit_point.y);
	// 			printf("ray orent %d \n", ray->orientation_wall_hit);
	// 		}
	// 		else
	// 			printf("Bloqueado\n");
	// 	}
	// 	else if (ray->is_facing_rigth == 1 && ray->orientation_wall_hit == -1)
	// 	{
	// 		printf("Rigth\n");
	// 		// // En este caso tocamos el muro en sentido este y no esta dentro del rango de nuestro jugador
	// 		if (!(ft_abs_double(ray->ray_vector.x) < 0.00001))
	// 		{
	// 			ray->distance = ((current_dda.x + 1) - rc->player.d_coords.x) / ray->ray_vector.x;
	// 			ray->hit_point.x = current_dda.x + 1;
	// 			ray->hit_point.y = rc->player.d_coords.y + (ray->distance * ray->ray_vector.y);
	// 			ray->orientation_wall_hit = 3;
	// 			printf("hit wall %d\n", hit_wall(data->map.map, &current_dda, &ray->orientation_wall_hit));
	// 		}
	// 		else
	// 			printf("Bloqueado\n");
	// 	}
	// }
}