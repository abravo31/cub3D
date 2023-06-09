#include "../../includes/cub3D_struct.h"

static void	check_hit(t_cub3D *data, t_ray *ray, t_vec2D *curr_dda, int *hit)
{
	int		map_elem;

	map_elem = -1;
	if ((int)curr_dda->y >= 0 && (int)curr_dda->y < data->map.max_h
		&& (int)curr_dda->x >= 0 && (int)curr_dda->x < data->map.max_w)
	{
		map_elem = data->map.map[(int)curr_dda->y][(int)curr_dda->x];
		if (map_elem == 1)
		{
			*hit = 1;
		}
		else if (map_elem >= 2 && map_elem <= 3)
		{
			*hit = handle_door_hit(data, ray, curr_dda);
		}
		else
			ray->orientation_wall_hit = -1;
	}
}

static void	horizontal_hit(t_ray *ray, t_vec2D *curr_dda, int ray_orientation)
{
	if (ray->hit_point.y > curr_dda->y && ray->hit_point.y < (curr_dda->y + 1))
	{
		ray->orientation_wall_hit = ray_orientation;
	}
	else if ((ft_abs_double(ray->hit_point.y - (curr_dda->y)) < 0.000001)
		&& ray->hit_point.y < (curr_dda->y + 1))
	{
		ray->orientation_wall_hit = ray_orientation;
	}
}

static void	hit_xy_axis(t_cub3D *data, t_rc *rc, t_ray *ray, t_vec2D *c_dda)
{
	if (ray->is_facing_left == 1 && ray->orientation_wall_hit == -1)
	{
		horizontal_hit(ray, c_dda, 4);
	}
	else if (ray->is_facing_rigth == 1 && ray->orientation_wall_hit == -1)
	{
		horizontal_hit(ray, c_dda, 3);
	}
	if (ray->is_facing_up == 1 && ray->orientation_wall_hit == -1)
	{
		equation_straight_line(rc, ray, c_dda->y, VERTICAL);
		if (ray->hit_point.x > c_dda->x && ray->hit_point.x < (c_dda->x + 1))
			ray->orientation_wall_hit = 1;
	}
	else if (ray->is_facing_down == 1 && ray->orientation_wall_hit == -1)
	{
		equation_straight_line(rc, ray, c_dda->y + 1, VERTICAL);
		if (ray->hit_point.x > c_dda->x && ray->hit_point.x < (c_dda->x + 1))
			ray->orientation_wall_hit = 2;
	}
}

static void	check_corners(t_cub3D *data, t_rc *rc, t_ray *ray, t_vec2D *curr_dda)
{
	double	curr_dda_vertical;
	double	curr_dda_horizontal;

	curr_dda_vertical = 0;
	curr_dda_horizontal = 0;
	if (ray->is_facing_rigth)
		curr_dda_horizontal = (curr_dda->x + 1);
	else if (ray->is_facing_left)
		curr_dda_horizontal = (curr_dda->x);
	equation_straight_line(rc, ray, curr_dda_horizontal, HORIZONTAL);
	if (ray->is_facing_up)
	{
		curr_dda_vertical = curr_dda->y;
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
		curr_dda_vertical = curr_dda->y + 1;
		if (ft_abs_double(ray->hit_point.y - curr_dda_vertical) < 0.00001)
		{
			if (ray->is_facing_rigth)
				ray->orientation_wall_hit = 7;
			else if (ray->is_facing_left)
				ray->orientation_wall_hit = 8;
		}
	}
}

static int	check_pos_player(t_cub3D *data, t_vec2D *curr_dda)
{
	int	pos_player;

	pos_player = data->map.map[(int)curr_dda->y][(int)curr_dda->x];
	if (pos_player == 2 || pos_player == 3)
		return (1);
	return (0);
}

static void	go_through_door(t_cub3D *data, t_ray *ray, t_vec2D pos_player)
{
	t_vec2D	initial_door;
	int		door_type;

	door_type = data->map.map[(int)pos_player.y][(int)pos_player.x];
	initial_door.y = (int)pos_player.y;
	initial_door.x = (int)pos_player.x;
	if (door_type == VERTICAL_DOOR)
	{
		if (ray->is_facing_up || ray->is_facing_down)
		{
			if (ray->hit_point.x >= initial_door.x && ray->hit_point.x <= (initial_door.x + 1.0))
			{
				ray->orientation_wall_hit = 6;
			}
		}
	}
	else if (door_type == HORIZONTAL_DOOR)
	{
		if (ray->is_facing_rigth || ray->is_facing_left)
		{
			if (ray->hit_point.y >= initial_door.y && ray->hit_point.y <= (initial_door.y + 1.0))
			{
				ray->orientation_wall_hit = 8;
			}
		}
	}
}

void	wall_finder(t_cub3D *data, t_ray *ray, t_rc *rc, int i)
{
	t_vec2D	curr_dda;
	t_vec2D	pos_player;
	int		event;
	int		hit;

	event = 0;
	hit = 0;
	get_int_coords(&data->rc.player, &pos_player);
	if (check_pos_player(data, &pos_player))
		event = 1;
	curr_dda.y = pos_player.y;
	curr_dda.x = pos_player.x;
	while (!hit)
	{
		check_corners(data, rc, ray, &curr_dda);
		hit_xy_axis(data, rc, ray, &curr_dda);
		if (ray->orientation_wall_hit == 1)
			curr_dda.y = curr_dda.y - 1;
		if (ray->orientation_wall_hit == 2)
			curr_dda.y = curr_dda.y + 1;
		if (ray->orientation_wall_hit == 3)
			curr_dda.x = curr_dda.x + 1;
		if (ray->orientation_wall_hit == 4)
			curr_dda.x = curr_dda.x - 1;
		dda_corners(data->map.map, ray, &curr_dda, &hit);
		check_hit(data, ray, &curr_dda, &hit);
	}
	if (event)
		go_through_door(data, ray, pos_player);
}
