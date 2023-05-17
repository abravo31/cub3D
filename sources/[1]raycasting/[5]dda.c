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

/******************************************************
This function is only for draw the position checked by dda
*******************************************************/

static void	draw_square_checked(t_cub3D *data, t_vec2D *current_dda)
{
	int	y;
	int	x;

	y = (int)current_dda->y * (int)data->rc.scale_map;
	x = (int)current_dda->x * (int)data->rc.scale_map;
	// //printf("y %d -- x %d\n", y, x);
	draw_square(data, y, x, 5, data->rc.scale_map);
}

static void	check_hit_Y_axis(t_cub3D *data, t_rc *rc, t_ray *ray, t_vec2D *current_dda)
{
	if (ray->is_facing_up == 1 && ray->orientation_wall_hit == -1)
	{
		ray->distance = (current_dda->y - rc->player.d_coords.y) / ray->ray_vector.y;
		ray->hit_point.x = rc->player.d_coords.x + (ray->distance * ray->ray_vector.x);
		ray->hit_point.y = current_dda->y;
		if (ray->hit_point.x > current_dda->x && ray->hit_point.x < (current_dda->x + 1))
			ray->orientation_wall_hit = 1;
	}
	else if (ray->is_facing_down == 1 && ray->orientation_wall_hit == -1)
	{
		ray->distance = ((current_dda->y + 1) - rc->player.d_coords.y) / ray->ray_vector.y;
		ray->hit_point.x = rc->player.d_coords.x + (ray->distance * ray->ray_vector.x);
		ray->hit_point.y = current_dda->y + 1;
		// En este caso tocamos el muro en sentido sur y esta dentro del rango de nuestro jugador
		if (ray->hit_point.x > current_dda->x && ray->hit_point.x < (current_dda->x + 1))
		{
			ray->orientation_wall_hit = 2;
		}
	}
	// draw_square_point(data, ray->hit_point);
}

static void	check_hit_X_axis(t_cub3D *data, t_rc *rc, t_ray *ray, t_vec2D *current_dda)
{
	// //printf("ray_vector x : %f -- y : %f\n", ray->ray_vector.x, ray->ray_vector.y);
	// //printf("current dda x : %f -- y : %f\n", current_dda->x, current_dda->y);
	if  (ray->is_facing_left == 1 && ray->orientation_wall_hit == -1)
	{
		//printf("Left\n");
		// if (!(ft_abs_double(ray->ray_vector.x) < 0.00001))
		// {
			ray->distance = ((current_dda->x) - rc->player.d_coords.x) / ray->ray_vector.x;
			ray->hit_point.x = current_dda->x;
			ray->hit_point.y = rc->player.d_coords.y + (ray->distance * ray->ray_vector.y);
			//printf("Hit pointX x %f - y %f\n", ray->hit_point.x, ray->hit_point.y);
			//printf("current dda y %f | x %f!\n", current_dda->y, current_dda->x);
			if (ray->hit_point.y > current_dda->y && ray->hit_point.y < (current_dda->y + 1))
			{
				ray->orientation_wall_hit = 4;
			}
		// }
	}
	else if (ray->is_facing_rigth == 1 && ray->orientation_wall_hit == -1)
	{
		//printf("Rigth\n");
		// // En este caso tocamos el muro en sentido este y no esta dentro del rango de nuestro jugador
		// if (!(ft_abs_double(ray->ray_vector.x) < 0.00001))
		// {
			ray->distance = ((current_dda->x + 1) - rc->player.d_coords.x) / ray->ray_vector.x;
			ray->hit_point.x = current_dda->x + 1;
			ray->hit_point.y = rc->player.d_coords.y + (ray->distance * ray->ray_vector.y);
			ray->orientation_wall_hit = 3;
			//printf("Hit pointX x %f - y %f\n", ray->hit_point.x, ray->hit_point.y);
			//printf("current dda y %f | x %f!\n", current_dda->y, current_dda->x);
			if (ray->hit_point.y > current_dda->y && ray->hit_point.y < (current_dda->y + 1))
			{
				ray->orientation_wall_hit = 3;
			}
	}
	// draw_square_point(data, ray->hit_point);
}

static void	check_corners(t_cub3D *data, t_rc *rc, t_ray *ray, t_vec2D *current_dda)
{
	if (ray->is_facing_up && ray->is_facing_rigth)
	{
		ray->distance = ((current_dda->x + 1) - rc->player.d_coords.x) / ray->ray_vector.x;
		ray->hit_point.y = rc->player.d_coords.y + (ray->distance * ray->ray_vector.y);
		ray->hit_point.x = current_dda->x + 1;
		if (ft_abs_double(ray->hit_point.y - current_dda->y) < 0.00001)
			ray->orientation_wall_hit = 5;
	}
	else if (ray->is_facing_up && ray->is_facing_left)
	{
		ray->distance = ((current_dda->x) - rc->player.d_coords.x) / ray->ray_vector.x;
		ray->hit_point.y = rc->player.d_coords.y + (ray->distance * ray->ray_vector.y);
		ray->hit_point.x = current_dda->x;
		if (ft_abs_double(ray->hit_point.y - current_dda->y) < 0.00001)
			ray->orientation_wall_hit = 6;
	}
	else if (ray->is_facing_down && ray->is_facing_rigth)
	{
		ray->distance = ((current_dda->x + 1) - rc->player.d_coords.x) / ray->ray_vector.x;
		ray->hit_point.y = rc->player.d_coords.y + (ray->distance * ray->ray_vector.y);
		ray->hit_point.x = current_dda->x + 1;
		if (ft_abs_double(ray->hit_point.y - (current_dda->y + 1)) < 0.00001)
			ray->orientation_wall_hit = 7;
	}
	else if (ray->is_facing_down && ray->is_facing_left)
	{
		ray->distance = ((current_dda->x) - rc->player.d_coords.x) / ray->ray_vector.x;
		ray->hit_point.y = rc->player.d_coords.y + (ray->distance * ray->ray_vector.y);
		ray->hit_point.x = current_dda->x;
		if (ft_abs_double(ray->hit_point.y - (current_dda->y + 1)) < 0.00001)
			ray->orientation_wall_hit = 8;
	}
}

void	wall_finder(t_cub3D *data, t_ray *ray, t_rc *rc)
{
	t_vec2D	current_dda;
	int		hit;
	int		i;

	get_int_coords(&data->rc.player);
	current_dda.x = rc->player.i_coords.x;
	current_dda.y = rc->player.i_coords.y;
	printf("Begin position x %f | y %f\n", current_dda.x, current_dda.y);
	hit = 0;
	while (!hit)
	{
		check_corners(data->map.map, rc, ray, &current_dda);
		check_hit_Y_axis(data, rc, ray, &current_dda);
		check_hit_X_axis(data, rc, ray, &current_dda);
		if (ray->orientation_wall_hit == 1)
			current_dda.y = current_dda.y - 1;
		if (ray->orientation_wall_hit == 2)
			current_dda.y = current_dda.y + 1;
		if (ray->orientation_wall_hit == 3)
			current_dda.x = current_dda.x + 1;
		if (ray->orientation_wall_hit == 4)
			current_dda.x = current_dda.x - 1;
		dda_corners(data->map.map, ray, &current_dda, &hit);
		//printf("current dda at y %d | x %d!\n", (int)current_dda.y, (int)current_dda.x);
		//printf("%c\n", (data->map.map[(int)current_dda.y][(int)current_dda.x]));
		if (data->map.map[(int)current_dda.y][(int)current_dda.x] == 1)
			hit = 1;
		else
			ray->orientation_wall_hit = -1;
	}
	//printf("Hit in map at y %d | x %d!\n", (int)current_dda.y, (int)current_dda.x);
	// draw_square_checked(data, &current_dda);
}