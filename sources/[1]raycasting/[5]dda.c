#include "../../includes/cub3D_struct.h"

static void	get_int_coords(t_player *player, t_vec2D *current_dda)
{
	double		integer_value;
	double		double_value;

	double_value = modf(player->d_coords.x, &integer_value);
	player->i_coords.x = (int)integer_value;
	double_value = modf(player->d_coords.y, &integer_value);
	player->i_coords.y = (int)integer_value;
    (void)double_value;
	current_dda->x = player->i_coords.x;
	current_dda->y = player->i_coords.y;
}

static void	equation_straight_line(t_rc *rc, t_ray *ray, double curr_dda, int dir)
{
	if (dir == VERTICAL)
	{
		ray->distance = (curr_dda - rc->player.d_coords.y) / ray->ray_vector.y;
		ray->hit_point.x = rc->player.d_coords.x + (ray->distance * ray->ray_vector.x);
		ray->hit_point.y = curr_dda;
	}
	else if (dir == HORIZONTAL)
	{
		ray->distance = (curr_dda - rc->player.d_coords.x) / ray->ray_vector.x;
		ray->hit_point.y = rc->player.d_coords.y + (ray->distance * ray->ray_vector.y);
		ray->hit_point.x = curr_dda;
	}
}

static void	check_hit(t_cub3D *data, t_ray *ray, t_vec2D *curr_dda, int *hit)
{
	int		map_elem;

	map_elem = -1;
	if ((int)curr_dda->y >= 0 && (int)curr_dda->y < data->map.max_h
		&& (int)curr_dda->x >= 0 && (int)curr_dda->x < data->map.max_w)
	{
		map_elem = data->map.map[(int)curr_dda->y][(int)curr_dda->x];
		if (map_elem >= 1 && map_elem <= 2)
		{
			*hit = 1;
			if (ray->distance < 0.6)
			{
				if (map_elem == 2)
				{
					if (!data->rc.doors)
						ray->orientation_wall_hit = 5;
					else
					{
						data->map.map[(int)curr_dda->y][(int)curr_dda->x] = 3;
						// printf("Ahora es un tres!\n");
					}
				}
			}
		}
		else if (map_elem == 3)
		{
			if (ray->distance < 0.6)
			{
				if (!data->rc.doors)
				{
					data->map.map[(int)curr_dda->y][(int)curr_dda->x] = 2;
					ray->orientation_wall_hit = 5;
				}
				else
					ray->orientation_wall_hit = -1;
			}
			else
				ray->orientation_wall_hit = -1;
		}
		else
			ray->orientation_wall_hit = -1;
	}
	
}
// /******************************************************
// This function is only for draw the rays in the screen
// *******************************************************/
// static void	draw_ray(t_cub3D *data, t_rc *rc, t_vec2D ray_hit_point)
// {
// 	t_vec2D		ray_hit_point_screen;
// 	t_vec2D		player_screen;

// 	player_screen = rc->player.d_coords;
// 	ray_hit_point_screen = scalar_mult(ray_hit_point, rc->scale_map);
// 	player_screen = scalar_mult(player_screen, rc->scale_map);
// 	ft_draw_line(data, player_screen, ray_hit_point_screen, 0xA020F0);
// }

// /******************************************************
// This function is only for draw the position checked by dda
// *******************************************************/

static void	draw_square_checked(t_cub3D *data, t_vec2D *current_dda)
{
	int	y;
	int	x;

	y = (int)current_dda->y * (int)data->rc.scale_map;
	x = (int)current_dda->x * (int)data->rc.scale_map;
	draw_square(data, y, x, 5, data->rc.scale_map);
}

static void	check_horizontal_hit(t_ray *ray, t_vec2D ray_hit_point, t_vec2D *current_dda, int ray_orientation)
{
	if (ray->hit_point.y > current_dda->y && ray->hit_point.y < (current_dda->y + 1))
	{
		ray->orientation_wall_hit = ray_orientation;
	}
	else if ((ft_abs_double(ray->hit_point.y - (current_dda->y)) < 0.000001)
		&& ray->hit_point.y < (current_dda->y + 1))
	{
		ray->orientation_wall_hit = ray_orientation;
	}
}

static void	check_hit_Y_axis(t_cub3D *data, t_rc *rc, t_ray *ray, t_vec2D *current_dda)
{
	if  (ray->is_facing_left == 1 && ray->orientation_wall_hit == -1)
	{
		// ray->distance = ((current_dda->x) - rc->player.d_coords.x) / ray->ray_vector.x;
		// ray->hit_point.x = current_dda->x;
		// ray->hit_point.y = rc->player.d_coords.y + (ray->distance * ray->ray_vector.y);
		check_horizontal_hit(ray, ray->hit_point, current_dda, 4);
	}
	else if (ray->is_facing_rigth == 1 && ray->orientation_wall_hit == -1)
	{
		// ray->distance = ((current_dda->x + 1) - rc->player.d_coords.x) / ray->ray_vector.x;
		// ray->hit_point.x = current_dda->x + 1;
		// ray->hit_point.y = rc->player.d_coords.y + (ray->distance * ray->ray_vector.y);
		check_horizontal_hit(ray, ray->hit_point, current_dda, 3);
	}
	if (ray->is_facing_up == 1 && ray->orientation_wall_hit == -1)
	{
		equation_straight_line(rc, ray, current_dda->y, VERTICAL);
		if (ray->hit_point.x > current_dda->x && ray->hit_point.x < (current_dda->x + 1))
			ray->orientation_wall_hit = 1;
	}
	else if (ray->is_facing_down == 1 && ray->orientation_wall_hit == -1)
	{
		equation_straight_line(rc, ray, current_dda->y + 1, VERTICAL);
		if (ray->hit_point.x > current_dda->x && ray->hit_point.x < (current_dda->x + 1))
			ray->orientation_wall_hit = 2;
	}
	// draw_square_point(data, ray->hit_point);
	// (void)data;
}

static void	check_hit_X_axis(t_cub3D *data, t_rc *rc, t_ray *ray, t_vec2D *current_dda)
{
	if  (ray->is_facing_left == 1 && ray->orientation_wall_hit == -1)
	{
		ray->distance = ((current_dda->x) - rc->player.d_coords.x) / ray->ray_vector.x;
		ray->hit_point.x = current_dda->x;
		ray->hit_point.y = rc->player.d_coords.y + (ray->distance * ray->ray_vector.y);
		check_horizontal_hit(ray, ray->hit_point, current_dda, 4);
	}
	else if (ray->is_facing_rigth == 1 && ray->orientation_wall_hit == -1)
	{
		ray->distance = ((current_dda->x + 1) - rc->player.d_coords.x) / ray->ray_vector.x;
		ray->hit_point.x = current_dda->x + 1;
		ray->hit_point.y = rc->player.d_coords.y + (ray->distance * ray->ray_vector.y);
		check_horizontal_hit(ray, ray->hit_point, current_dda, 3);
	}
	// draw_square_point(data, ray->hit_point);
	(void)data;
}

static void	check_corners(t_cub3D *data, t_rc *rc, t_ray *ray, t_vec2D *current_dda)
{
	double	curr_dda_vertical;
	double	curr_dda_horizontal;

	if (ray->is_facing_rigth)
		curr_dda_horizontal = (current_dda->x + 1);
	else if (ray->is_facing_left)
		curr_dda_horizontal = (current_dda->x);
	equation_straight_line(rc, ray, curr_dda_horizontal, HORIZONTAL);
	if (ray->is_facing_up)
	{
		curr_dda_vertical = current_dda->y;
		if (ft_abs_double(ray->hit_point.y - curr_dda_vertical) < 0.00001)
		{
			if (ray->is_facing_rigth)
				ray->orientation_wall_hit = 5;
			else if (ray->is_facing_left)
				ray->orientation_wall_hit = 6;
		}
	}
	else if (ray->is_facing_down)
	{
		curr_dda_vertical = current_dda->y + 1;
		if (ft_abs_double(ray->hit_point.y - curr_dda_vertical) < 0.00001)
		{
			if (ray->is_facing_rigth)
				ray->orientation_wall_hit = 7;
			else if (ray->is_facing_left)
				ray->orientation_wall_hit = 8;
		}
	}
	// draw_square_point(data, ray->hit_point);
	(void)data;
}

static void	check_corners_down(t_cub3D *data, t_rc *rc, t_ray *ray, t_vec2D *current_dda)
{
	if (ray->is_facing_down && ray->is_facing_rigth)
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
	// draw_square_point(data, ray->hit_point);
	(void)data;
}

static void	print_ray_info_debug(t_ray *ray, int i)
{
	printf("It's the ray number %d\n", i);
	printf("ray->is_facing_down :%d\n", ray->is_facing_down);
	printf("ray->is_facing_up :%d\n", ray->is_facing_up);
	printf("ray->is_facing_rigth :%d\n", ray->is_facing_rigth);
	printf("ray->is_facing_left :%d\n", ray->is_facing_left);
	printf("ray vector x %f | y %f\n", ray->ray_vector.x, ray->ray_vector.y);
	printf("hit point vector x %f | y %f\n", ray->hit_point.x, ray->hit_point.y);
}

// void	wall_finder(t_cub3D *data, t_ray *ray, t_rc *rc)
void	wall_finder(t_cub3D *data, t_ray *ray, t_rc *rc, int i)
{
	t_vec2D	current_dda;
	int		hit;

	get_int_coords(&data->rc.player, &current_dda);
	hit = 0;
	while (!hit)
	{
		check_corners(data, rc, ray, &current_dda);
		check_hit_Y_axis(data, rc, ray, &current_dda);
		// check_hit_X_axis(data, rc, ray, &current_dda);
		// print_ray_info_debug(ray, i);
		printf("orientation wall hit %d\n", ray->orientation_wall_hit);
		if (ray->orientation_wall_hit == 1)
			current_dda.y = current_dda.y - 1;
		if (ray->orientation_wall_hit == 2)
			current_dda.y = current_dda.y + 1;
		if (ray->orientation_wall_hit == 3)
			current_dda.x = current_dda.x + 1;
		if (ray->orientation_wall_hit == 4)
			current_dda.x = current_dda.x - 1;
		dda_corners(data->map.map, ray, &current_dda, &hit);
		check_hit(data, ray, &current_dda, &hit);
		// draw_square_checked(data, &current_dda);
	}
	if (ray->orientation_wall_hit == -1)
		printf("Hereee\n");
	// printf("Hit in map at y %d | x %d!\n", (int)current_dda.y, (int)current_dda.x);
	// draw_square_checked(data, &current_dda);
}