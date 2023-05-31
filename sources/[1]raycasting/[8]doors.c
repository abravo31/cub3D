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
			// printf("hit point x %f | y %f\n", ray->hit_point.x, ray->hit_point.y);
			draw_square_point(data, ray->hit_point);
			orientation_wall_hit = 1;
		}
	}
	if (orientation_wall_hit == -1)
	{
		// printf("Entramos a este caso\n");
		equation_straight_line(rc, ray, door->next_dda.x, HORIZONTAL);
		// printf("hit point x %f | y %f\n", ray->hit_point.x, ray->hit_point.y);
		if (!((ray->hit_point.y < door->initial_dda.y) || (ray->hit_point.x > (door->initial_dda.y + 1))))
		{
			// printf("hit point x %f | y %f\n", ray->hit_point.x, ray->hit_point.y);
			draw_square_point(data, ray->hit_point);
			orientation_wall_hit = 1;
		}
	}
}

static void	next_point_hit_vertical_closed(t_cub3D *data, t_rc *rc, t_ray *ray, t_door *door, int dir)
{
	equation_straight_line(rc, ray, door->next_dda.x, HORIZONTAL);
	// draw_square_point(data, ray->hit_point);
	// printf("cuando buscamos en la mitad hit point x %f | y %f\n", ray->hit_point.x, ray->hit_point.y);
	if (ray->hit_point.y < door->initial_dda.y || ray->hit_point.y > (door->initial_dda.y + 1.0))
	{
		equation_straight_line(rc, ray, door->next_dda.y, VERTICAL);
		// draw_square_point(data, ray->hit_point);
		// printf("cuando buscamos en los lados x %f | y %f\n", ray->hit_point.x, ray->hit_point.y);
		door->orientation_hit = 7;
	}
	else
		door->orientation_hit = 6;
	draw_square_point(data, ray->hit_point);
}

static void	next_point_hit_vertical_open(t_cub3D *data, t_rc *rc, t_ray *ray, t_door *door, int dir)
{
	equation_straight_line(rc, ray, door->next_dda.x, VERTICAL);
	printf("hit point x %f | y %f\n", ray->hit_point.x, ray->hit_point.y);
	printf("next dda x %f | y %f \n", door->next_dda.x, door->next_dda.y);
	// draw_square_point(data, ray->hit_point);
	if ((ray->hit_point.x >= door->initial_dda.x) && (ray->hit_point.x <= door->next_dda.x))
	{
		door->orientation_hit = 6;
		printf("Pego\n");
	}
	else
		printf("debe seguir!\n");
}

static void	next_point_hit_vertical_opening(t_cub3D *data, t_rc *rc, t_ray *ray, t_door *door, int dir)
{
	float	current_timer;

	current_timer = ((door->initial_dda.y + 1.0) - (*door->timer));
	equation_straight_line(&data->rc, ray, door->next_dda.x, dir);
	// printf("hit point x %f | y %f\n", ray->hit_point.x, ray->hit_point.y);
	// printf("next dda x %f | y %f \n", door->next_dda.x, door->next_dda.y);
	// draw_square_point(data, ray->hit_point);
	printf("choque con puerta hit point x %f | y %f\n", ray->hit_point.x, ray->hit_point.y);
	printf("comparando entre >= door->initial_dda.y %f && <= curren timer %f\n", door->initial_dda.y, current_timer);
	if ((ray->hit_point.y >= door->initial_dda.y) && (ray->hit_point.y <= current_timer))
	{
		ray->orientation_wall_hit = 6;
		printf("Pego\n");
	}
	else
	{
		printf("initial dda y %f\n", door->initial_dda.y);
		if (ray->is_facing_up)
		{
			door->next_dda.y = door->initial_dda.y;
		}
		else if (ray->is_facing_down)
		{
			door->next_dda.y = door->initial_dda.y + 1.0;
		}
		printf("next dda %f\n", door->next_dda.y);
		printf("next dda %f\n", door->next_dda.x);
		equation_straight_line(&data->rc, ray, door->next_dda.y, VERTICAL);
		printf("choque con lados hit point x %f | y %f\n", ray->hit_point.x, ray->hit_point.y);
		printf("comparando entre >= door->initial_dda.x %f && <= (door->initial_dda.x + 1.0) %f\n", door->initial_dda.x, (door->initial_dda.x + 1.0));
		if ((ray->hit_point.x >= door->initial_dda.x) && (ray->hit_point.y <= (door->initial_dda.x + 1.0)))
		{
			ray->orientation_wall_hit = 7;
			printf("Pego por un lado\n");
			draw_square_point(data, ray->hit_point);
		}
		else
		{
			printf("Debe continuar con orientation wall hit %d\n", ray->orientation_wall_hit);
		}
	}
}

static void	handle_vertical_door(t_cub3D *data, t_ray *ray, t_door *door, int *hit_d)
{
	/************Init line of door *****************/
	if (ray->is_facing_up)
		door->next_dda.y = door->initial_dda.y;
	else if (ray->is_facing_down)
		door->next_dda.y = door->initial_dda.y + 1;
	if ((*door->status) == CLOSED)
	{
		/*Como chequeamos la casilla conforme al mapa*/
		if (ray->is_facing_rigth || ray->is_facing_left)
			door->next_dda.x = door->initial_dda.x + 0.5;
		// printf("next dda x %f | y %f\n", door->next_dda.x, door->next_dda.y);
		next_point_hit_vertical_closed(data, &data->rc, ray, door, VERTICAL);
		ray->orientation_wall_hit = door->orientation_hit;
		*hit_d = 1;
	}
	if ((*door->status) == OPEN)
	{
		printf("It's open!\n");
		if (ray->is_facing_rigth || ray->is_facing_left)
		{
			if (!ray->is_facing_up && !ray->is_facing_down)
			{
				printf("Esto pasa y ya!\n");
				*hit_d = 0;
			}
			else
			{
				door->next_dda.x = door->initial_dda.x + 1.0;
				printf("Este es el caso que aun no he terminado de gestionar\n");
			}
		}
		printf("next dda x %f | y %f\n", door->next_dda.x, door->next_dda.y);
		if (*hit_d == -1)
		{
			next_point_hit_vertical_open(data, &data->rc, ray, door, VERTICAL);
			if (door->orientation_hit == -1)
				*hit_d = 0;
			else
			{
				ray->orientation_wall_hit = door->orientation_hit;
				*hit_d = 1;
			}
		}
	}
	if ((*door->status) == OPENING)
	{
		printf("La puerta esta opening\n");
		if (ray->is_facing_rigth || ray->is_facing_left)
			door->next_dda.x = door->initial_dda.x + 0.5;
		next_point_hit_vertical_opening(data, &data->rc, ray, door, HORIZONTAL);
		if (ray->orientation_wall_hit != -1)
			*hit_d = 1;
		else
			*hit_d = 0;
	}
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
				// check_door_hook(rc, door);
			}
		}
		else if (ray->is_facing_down)
		{
			if (rc->center_screen.y >= (door->initial_dda.y + 0.5))
			{
				printf("Here I can open the door in the down\n");
				printf("Value of hook for doors %d\n", rc->doors);
				// check_door_hook(rc, door);
			}
		}
	}
}

int	handle_door_hit(t_cub3D *data, t_ray *ray, t_vec2D *curr_dda)
{
	t_rc	*rc;
	t_door	door;
	int		value;

	rc = &data->rc;
	if (data->door.status == NULL)
	{
		printf("Voy a init\n");
		init_door(data, &data->door, curr_dda);
		value = get_next_hit(data, ray, &data->door);
	}
	else
	{
		ray->orientation_wall_hit = -1;
		// printf("Por aqui pasa\n");
		value = get_next_hit(data, ray, &data->door);
	}
	return (value);
}