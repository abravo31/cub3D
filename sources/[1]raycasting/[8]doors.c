#include "../../includes/cub3D_struct.h"

static void	init_door(t_cub3D *data, t_door *d, t_vec2D *curr_dda)
{
	d->orientation_hit = -1;
	d->type_door = data->map.map[(int)curr_dda->y][(int)curr_dda->x];
	d->status = &data->map.door_state_map[(int)curr_dda->y][(int)curr_dda->x];
	d->timer = &data->map.timer_map[(int)curr_dda->y][(int)curr_dda->x];
	d->initial_dda.x = curr_dda->x;
	d->initial_dda.y = curr_dda->y;
	d->next_dda.x = -1;
	d->next_dda.y = -1;
}

static void	next_point_hit_vertical_closed(t_cub3D *data, t_rc *rc, t_ray *ray, t_door *door, int dir)
{
	if (dir == VERTICAL)
	{
		equation_straight_line(rc, ray, door->next_dda.x, HORIZONTAL);
		// printf("initial dda y %f | %f | %f\n", door->initial_dda.y, door->initial_dda.y + 1.0, door->next_dda.y);
		if (ray->hit_point.y < door->initial_dda.y || ray->hit_point.y > door->initial_dda.y + 1.0)
		{
			equation_straight_line(rc, ray, door->next_dda.y, VERTICAL);
			ray->orientation_wall_hit = 6;
		}
		else
			ray->orientation_wall_hit = 5;
	}
	else if (dir == HORIZONTAL)
	{
		equation_straight_line(rc, ray, door->next_dda.y, VERTICAL);
		if (ray->hit_point.x < door->initial_dda.x || ray->hit_point.x > (door->initial_dda.x + 1.0))
		{
			equation_straight_line(rc, ray, door->next_dda.x, HORIZONTAL);
			ray->orientation_wall_hit = 6;
		}
		else
			ray->orientation_wall_hit = 5;
	}
	draw_square_point(data, ray->hit_point);
}

static void	next_point_hit_vertical_open(t_cub3D *data, t_rc *rc, t_ray *ray, t_door *door, int dir)
{
	if (dir == VERTICAL)
	{
		equation_straight_line(&data->rc, ray, door->next_dda.y, VERTICAL);
		if ((ray->hit_point.x >= door->initial_dda.x) && (ray->hit_point.x <= door->next_dda.x))
			ray->orientation_wall_hit = 6;
	}
	else if (dir == HORIZONTAL)
	{
		equation_straight_line(&data->rc, ray, door->next_dda.x, HORIZONTAL);
		if ((ray->hit_point.y >= door->initial_dda.y) && (ray->hit_point.y <= door->next_dda.y))
			ray->orientation_wall_hit = 6;
	}
}

static void	next_point_hit_vertical_opening(t_cub3D *data, t_rc *rc, t_ray *ray, t_door *door, int dir)
{
	float	current_timer;

	current_timer = ((door->initial_dda.y + 1.0) - (*door->timer));
	equation_straight_line(&data->rc, ray, door->next_dda.x, dir);
	if ((ray->hit_point.y >= door->initial_dda.y) && (ray->hit_point.y <= current_timer))
		ray->orientation_wall_hit = 5;
	else
	{
		equation_straight_line(&data->rc, ray, door->next_dda.y, VERTICAL);
		if ((ray->hit_point.x >= door->initial_dda.x) && (ray->hit_point.x <= (door->initial_dda.x + 1.0)))
		{
			ray->orientation_wall_hit = 6;
		}
	}
}

static void	next_point_hit_horizontal_opening(t_cub3D *data, t_rc *rc, t_ray *ray, t_door *door, int dir)
{
	float	current_timer;

	current_timer = ((door->initial_dda.x + 1.0) - (*door->timer));
	equation_straight_line(&data->rc, ray, door->next_dda.y, dir);
	if ((ray->hit_point.x >= door->initial_dda.x) && (ray->hit_point.x <= current_timer))
		ray->orientation_wall_hit = 5;
	else
	{
		equation_straight_line(&data->rc, ray, door->next_dda.x, HORIZONTAL);
		if ((ray->hit_point.y >= door->initial_dda.y) && (ray->hit_point.y <= (door->initial_dda.y + 1.0)))
		{
			ray->orientation_wall_hit = 6;
		}
	}
}

static void	next_point_hit_vertical_closing(t_cub3D *data, t_rc *rc, t_ray *ray, t_door *door, int dir)
{
	float	current_timer;

	current_timer = ((door->initial_dda.y + 1.0) - (*door->timer));
	equation_straight_line(&data->rc, ray, door->next_dda.x, dir);
	if ((ray->hit_point.y >= door->initial_dda.y) && (ray->hit_point.y <= current_timer))
		ray->orientation_wall_hit = 5;
	else
	{
		equation_straight_line(&data->rc, ray, door->next_dda.y, VERTICAL);
		if ((ray->hit_point.x >= door->initial_dda.x) && (ray->hit_point.x <= (door->initial_dda.x + 1.0)))
			ray->orientation_wall_hit = 6;
	}
}

static void	next_point_hit_horizontal_closing(t_cub3D *data, t_rc *rc, t_ray *ray, t_door *door, int dir)
{
	float	current_timer;

	current_timer = ((door->initial_dda.x + 1.0) - (*door->timer));
	equation_straight_line(&data->rc, ray, door->next_dda.y, dir);
	if ((ray->hit_point.x >= door->initial_dda.x) && (ray->hit_point.x <= current_timer))
		ray->orientation_wall_hit = 5;
	else
	{
		equation_straight_line(&data->rc, ray, door->next_dda.x, HORIZONTAL);
		if ((ray->hit_point.y >= door->initial_dda.y) && (ray->hit_point.y <= (door->initial_dda.y + 1.0)))
			ray->orientation_wall_hit = 6;
	}
}

static int	init_new_points_horizontal(t_cub3D *data, t_ray *ray, t_door *door)
{
	if ((*door->status) == OPEN)
	{
		if (ray->is_facing_up || ray->is_facing_down)
		{
			door->next_dda.y = door->initial_dda.y + 1.0;
			if (!ray->is_facing_rigth && !ray->is_facing_left)
			{
				ray->orientation_wall_hit = -1;
				return (1);
			}
		}
	}
	else
		door->next_dda.y = door->initial_dda.y + 0.5;
	if (ray->is_facing_left)
		door->next_dda.x = door->initial_dda.x;
	else if (ray->is_facing_rigth)
		door->next_dda.x = door->initial_dda.x + 1.0;
	return (0);
}


static void	handle_horizontal_door(t_cub3D *data, t_ray *ray, t_door *door, int *hit_d)
{
	if ((*door->status) == CLOSED)
		next_point_hit_vertical_closed(data, &data->rc, ray, door, HORIZONTAL);
	else if ((*door->status) == OPEN)
		next_point_hit_vertical_open(data, &data->rc, ray, door, HORIZONTAL);
	else if ((*door->status) == OPENING)
		next_point_hit_horizontal_opening(data, &data->rc, ray, door, VERTICAL);
	else if ((*door->status) == CLOSING)
		next_point_hit_horizontal_closing(data, &data->rc, ray, door, HORIZONTAL);
}

static int	init_new_points_vertical(t_cub3D *data, t_ray *ray, t_door *door)
{
	if ((*door->status) == OPEN)
	{
		if (ray->is_facing_rigth || ray->is_facing_left)
		{
			door->next_dda.x = door->initial_dda.x + 1.0;
			if (!ray->is_facing_up && !ray->is_facing_down)
			{
				ray->orientation_wall_hit = -1;
				return (1);
			}
		}
	}
	else
		door->next_dda.x = door->initial_dda.x + 0.5;
	if (ray->is_facing_up)
		door->next_dda.y = door->initial_dda.y;
	else if (ray->is_facing_down)
		door->next_dda.y = door->initial_dda.y + 1.0;
	return (0);
}

static void	handle_vertical_door(t_cub3D *data, t_ray *ray, t_door *door, int *hit_d)
{
	if ((*door->status) == CLOSED)
		next_point_hit_vertical_closed(data, &data->rc, ray, door, VERTICAL);
	else if ((*door->status) == OPEN)
		next_point_hit_vertical_open(data, &data->rc, ray, door, VERTICAL);
	else if ((*door->status) == OPENING)
		next_point_hit_vertical_opening(data, &data->rc, ray, door, HORIZONTAL);
	else if ((*door->status) == CLOSING)
		next_point_hit_vertical_closing(data, &data->rc, ray, door, HORIZONTAL);
}

static int	get_next_hit(t_cub3D *data, t_ray *ray, t_door *door)
{
	t_vec2D	next_dda;
	int		hit_door;

	hit_door = -1;
	ray->orientation_wall_hit = -1;
	if (door->type_door == HORIZONTAL_DOOR)
	{
		if (!init_new_points_horizontal(data, ray, door))
		{
			handle_horizontal_door(data, ray, door, &hit_door);
		}
	}
	else if (door->type_door == VERTICAL_DOOR)
	{
		if (!init_new_points_vertical(data, ray, door))
		{
			handle_vertical_door(data, ray, door, &hit_door);
		}
	}
	if (ray->orientation_wall_hit != -1)
		hit_door = 1;
	else
		hit_door = 0;
	return (hit_door);
}

int	handle_door_hit(t_cub3D *data, t_ray *ray, t_vec2D *curr_dda)
{
	t_rc	*rc;
	t_door	door;
	int		value;

	rc = &data->rc;
	if (ray->ray_type != 1)
	{
		init_door(data, &data->door, curr_dda);
		value = get_next_hit(data, ray, &data->door);
		return (value);
	}
	return (1);
}