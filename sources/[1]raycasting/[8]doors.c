#include "../../includes/cub3D_struct.h"


static void	next_point_hit_horizontal(t_cub3D *data, t_rc *rc, t_ray *ray, t_door *door, int dir)
{
	int	orientation_wall_hit;

	orientation_wall_hit = -1;
	if (ray->is_facing_up || ray->is_facing_down)
	{
		equation_straight_line(rc, ray, door->next_dda.y, VERTICAL);
		if (!((ray->hit_point.x < door->initial_dda.x) || (ray->hit_point.x > (door->initial_dda.x + 1))))
		{
			// //printf("hit point x %f | y %f\n", ray->hit_point.x, ray->hit_point.y);
			draw_square_point(data, ray->hit_point);
			orientation_wall_hit = 1;
		}
	}
	if (orientation_wall_hit == -1)
	{
		// //printf("Entramos a este caso\n");
		equation_straight_line(rc, ray, door->next_dda.x, HORIZONTAL);
		// //printf("hit point x %f | y %f\n", ray->hit_point.x, ray->hit_point.y);
		if (!((ray->hit_point.y < door->initial_dda.y) || (ray->hit_point.x > (door->initial_dda.y + 1))))
		{
			// //printf("hit point x %f | y %f\n", ray->hit_point.x, ray->hit_point.y);
			draw_square_point(data, ray->hit_point);
			orientation_wall_hit = 1;
		}
	}
}

static void	next_point_hit_vertical_closed(t_cub3D *data, t_rc *rc, t_ray *ray, t_door *door, int dir)
{
	equation_straight_line(rc, ray, door->next_dda.x, HORIZONTAL);
	if (ray->hit_point.y < door->initial_dda.y || ray->hit_point.y > (door->initial_dda.y + 1.0))
	{
		equation_straight_line(rc, ray, door->next_dda.y, VERTICAL);
		ray->orientation_wall_hit = 7;
	}
	else
		ray->orientation_wall_hit = 6;
	draw_square_point(data, ray->hit_point);
}

static void	next_point_hit_vertical_open(t_cub3D *data, t_rc *rc, t_ray *ray, t_door *door, int dir)
{
	equation_straight_line(&data->rc, ray, door->next_dda.y, VERTICAL);
	// printf("hit point x %f | y %f\n", ray->hit_point.x, ray->hit_point.y);
	// printf("initial x %f | next %f\n", door->initial_dda.x, door->next_dda.x);
	if ((ray->hit_point.x >= door->initial_dda.x) && (ray->hit_point.x <= door->next_dda.x))
		ray->orientation_wall_hit = 7;
	// printf("Despues de %d\n", ray->orientation_wall_hit);
}

static void	next_point_hit_vertical_opening(t_cub3D *data, t_rc *rc, t_ray *ray, t_door *door, int dir)
{
	float	current_timer;

	current_timer = ((door->initial_dda.y + 1.0) - (*door->timer));
	equation_straight_line(&data->rc, ray, door->next_dda.x, dir);
	if ((ray->hit_point.y >= door->initial_dda.y) && (ray->hit_point.y <= current_timer))
		ray->orientation_wall_hit = 6;
	else
	{
		if (ray->is_facing_up)
			door->next_dda.y = door->initial_dda.y;
		else if (ray->is_facing_down)
			door->next_dda.y = door->initial_dda.y + 1.0;
		else
			return ;
		equation_straight_line(&data->rc, ray, door->next_dda.y, VERTICAL);
		// printf("hit point x %f | y %f\n", ray->hit_point.x, ray->hit_point.y);
		// printf("initial x %f | next %f\n", door->initial_dda.x, (door->initial_dda.x + 1.0));
		if ((ray->hit_point.x >= door->initial_dda.x) && (ray->hit_point.x <= (door->initial_dda.x + 1.0)))
		{
			ray->orientation_wall_hit = 7;
		}
	}
}

static void	next_point_hit_vertical_closing(t_cub3D *data, t_rc *rc, t_ray *ray, t_door *door, int dir)
{
	float	current_timer;

	current_timer = ((door->initial_dda.y + 1.0) - (*door->timer));
	// printf("current timer %f\n", current_timer);
	equation_straight_line(&data->rc, ray, door->next_dda.x, dir);
	if ((ray->hit_point.y >= door->initial_dda.y) && (ray->hit_point.y <= current_timer))
		ray->orientation_wall_hit = 6;
	else
	{
		if (ray->is_facing_up)
			door->next_dda.y = door->initial_dda.y;
		else if (ray->is_facing_down)
			door->next_dda.y = door->initial_dda.y + 1.0;
		else
			return ;
		equation_straight_line(&data->rc, ray, door->next_dda.y, VERTICAL);
		if ((ray->hit_point.x >= door->initial_dda.x) && (ray->hit_point.x <= (door->initial_dda.x + 1.0)))
			ray->orientation_wall_hit = 7;
	}
}

static void	handle_vertical_door(t_cub3D *data, t_ray *ray, t_door *door, int *hit_d)
{
	/************Init line of door *****************/
	if (ray->is_facing_up)
		door->next_dda.y = door->initial_dda.y;
	else if (ray->is_facing_down)
		door->next_dda.y = door->initial_dda.y + 1.0;
	if (ray->is_facing_rigth || ray->is_facing_left)
			door->next_dda.x = door->initial_dda.x + 0.5;
	// printf("****** Este rayo toca la puerta ******\n");
	// printf("Antes de %d\n", ray->orientation_wall_hit);
	ray->orientation_wall_hit = -1;
	if ((*door->status) == CLOSED)
	{
		next_point_hit_vertical_closed(data, &data->rc, ray, door, VERTICAL);
	}
	else if ((*door->status) == OPEN)
	{
		if (ray->is_facing_rigth || ray->is_facing_left)
		{
			door->next_dda.x = door->initial_dda.x + 1.0;
			if (!ray->is_facing_up && !ray->is_facing_down)
			{
				*hit_d = 0;
				// printf("Este no se analiza\n");
				return ;
			}
		}
		next_point_hit_vertical_open(data, &data->rc, ray, door, VERTICAL);
	}
	else if ((*door->status) == OPENING)
		next_point_hit_vertical_opening(data, &data->rc, ray, door, HORIZONTAL);
	else if ((*door->status) == CLOSING)
		next_point_hit_vertical_closing(data, &data->rc, ray, door, HORIZONTAL);
	if (ray->orientation_wall_hit != -1)
		*hit_d = 1;
	else
		*hit_d = 0;
}

static int	get_next_hit(t_cub3D *data, t_ray *ray, t_door *door)
{
	t_vec2D	next_dda;
	int		hit_door;

	hit_door = -1;
	if (door->type_door == HORIZONTAL_DOOR)
	{
		if (ray->is_facing_up || ray->is_facing_down)
		{
			door->next_dda.y = door->initial_dda.y + 0.5;
		}
		if (ray->is_facing_rigth)
		{
			door->next_dda.x = door->initial_dda.x + 1.0;
		}
		else if (ray->is_facing_left)
		{
			door->next_dda.x = door->initial_dda.x;
		}
		next_point_hit_horizontal(data, &data->rc, ray, door, VERTICAL);
	}
	else if (door->type_door == VERTICAL_DOOR)
	{
		handle_vertical_door(data, ray, door, &hit_door);
	}
	return (hit_door);
}

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

int	handle_door_hit(t_cub3D *data, t_ray *ray, t_vec2D *curr_dda)
{
	t_rc	*rc;
	t_door	door;
	int		value;

	rc = &data->rc;
	if (data->door.status == NULL)
	{
		init_door(data, &data->door, curr_dda);
	}
	if (ray->ray_type != 1)
	{
		// if ((*data->door.status) == CLOSED)
		// 	printf("Door is closed\n");
		// else if ((*data->door.status) == OPEN)
		// 	printf("Door is open\n");
		// //printf("orientation hit at the begin %d\n", ray->orientation_wall_hit);
		value = get_next_hit(data, ray, &data->door);
		// //printf("value to returned %d\n", value);
		return (value);
	}
	return (1);
}