#include "../../includes/cub3D_struct.h"


static void	next_point_hit_horizontal(t_cub3D *data, t_rc *rc, t_ray *ray, t_door *door, int dir)
{
	int	orientation_wall_hit;

	orientation_wall_hit = -1;
	if (ray->is_facing_up || ray->is_facing_down)
	{
		equation_straight_line(rc, ray, door->next_dda.y, VERTICAL);
		if (!((ray->hit_point.x < door->initial_dda->x) || (ray->hit_point.x > (door->initial_dda->x + 1))))
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
		if (!((ray->hit_point.y < door->initial_dda->y) || (ray->hit_point.x > (door->initial_dda->y + 1))))
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
	door->orientation_hit = 6;
	if (ray->hit_point.y < door->initial_dda->y || ray->hit_point.y > (door->initial_dda->y + 1.0))
	{
		equation_straight_line(rc, ray, door->next_dda.y, VERTICAL);
		door->orientation_hit = 7;
	}
	draw_square_point(data, ray->hit_point);
}

static void	next_point_hit_vertical_opening(t_cub3D *data, t_rc *rc, t_ray *ray, t_door *door, int dir)
{
	equation_straight_line(rc, ray, door->next_dda.x, HORIZONTAL);
	printf("hit point for search in the middle of the door square x %f | y %f\n", ray->hit_point.x, ray->hit_point.y);
	if (ray->hit_point.y < door->initial_dda->y || ray->hit_point.y > (door->initial_dda->y + 1.0))
	{
		printf("We go so far, we calculate the hit point in the side\n");
		equation_straight_line(rc, ray, door->next_dda.y, VERTICAL);
		printf("hit point for search in the middle of the door square x %f | y %f\n", ray->hit_point.x, ray->hit_point.y);
		door->orientation_hit = 7;
	}
	if (door->orientation_hit == -1)
	{
		// printf("First condition %d\n", ray->hit_point.y >= door->initial_dda->y);
		// printf("Second condition %d\n", ray->hit_point.y <= ((door->initial_dda->y + 1.0) - (*door->timer)));
		if (ray->hit_point.y >= door->initial_dda->y && ray->hit_point.y <= ((door->initial_dda->y + 1.0) - (*door->timer)))
		{
			door->orientation_hit = 6;
		}
		else
		{
			printf("door->next_dda.y %f\n", door->next_dda.y);
			equation_straight_line(rc, ray, door->next_dda.y, VERTICAL);
			printf("hit point for search after the closure of door x %f | y %f\n", ray->hit_point.x, ray->hit_point.y);
			if (ray->hit_point.x >= door->initial_dda->x && ray->hit_point.x <= (door->initial_dda->x + 1.0))
				door->orientation_hit = 7;
		}
	}
	// if (ray->hit_point.y < door->initial_dda->y || ray->hit_point.y > (door->initial_dda->y + 1.0))
	// {
	// 	printf("Esta afuera\n");
	// 	equation_straight_line(rc, ray, door->next_dda.y, VERTICAL);
	// 	door->orientation_hit = 7;
	// }
	// if (ray->hit_point.y >= door->initial_dda->y && ray->hit_point.y <= ((door->initial_dda->y + 1.0) - (*door->timer)))
	// {
	// 	// printf("Se puede decir que golpeo\n");
	// 	door->orientation_hit = 6;
	// 	// printf("Esta por fuera y por eso volvemos \n");
	// 	// equation_straight_line(rc, ray, door->next_dda.y, VERTICAL);
	// }
	// else
	// {
	// 	door->orientation_hit = -1;
	// }
	draw_square_point(data, ray->hit_point);
	if (door->orientation_hit == 6)
		printf("Pego en la puerta!\n");
	else if (door->orientation_hit == 7)
		printf("Pego en un costado!\n");
	else
		printf("Debe seguir\n");
	door->orientation_hit = -1;
}

static void	get_next_hit(t_cub3D *data, t_ray *ray, t_door *door)
{
	t_vec2D	next_dda;

	if (door->type_door == HORIZONTAL_DOOR)
	{
		// printf("o here\n");
		if (ray->is_facing_up || ray->is_facing_down)
		{
			door->next_dda.y = door->initial_dda->y + 0.5;
		}
		if (ray->is_facing_rigth)
		{
			door->next_dda.x = door->initial_dda->x + 1.0;
		}
		else if (ray->is_facing_left)
		{
			door->next_dda.x = door->initial_dda->x;
		}
		next_point_hit_horizontal(data, &data->rc, ray, door, VERTICAL);
	}
	else if (door->type_door == VERTICAL_DOOR)
	{
		/************Init line of door *****************/
		if (ray->is_facing_rigth || ray->is_facing_left)
		{
			door->next_dda.x = door->initial_dda->x + 0.5;
		}
		if (ray->is_facing_up)
		{
			door->next_dda.y = door->initial_dda->y;
		}
		else if (ray->is_facing_down)
		{
			door->next_dda.y = door->initial_dda->y + 1;
		}
		if ((*door->status) == CLOSED)
		{
			next_point_hit_vertical_closed(data, &data->rc, ray, door, VERTICAL);
		}
		else if  ((*door->status) == OPENING)
		{
			printf("initial dda x %f | y %f\n", door->initial_dda->x, door->initial_dda->y);
			printf("door->initial_dda->y  %f | ((door->initial_dda->y + 1.0) - (*door->timer)) %f\n", door->initial_dda->y, ((door->initial_dda->y + 1.0) - (*door->timer)));
			while ((*door->timer) <= door->timer_direction)
			{
				// printf("timer in the loop %f\n", (*door->timer));
				next_point_hit_vertical_opening(data, &data->rc, ray, door, VERTICAL);
				// printf("%d\n", door->orientation_hit);
				(*door->timer) = (*door->timer) + 0.1;
			}
		}
		// printf("here\n");
		// printf("Debo buscar el siguiente punto en y\n");
	}

	// // When the door is complety closed
	// if ((*door->status) == CLOSED)
	// {
	// 	// printf("initial dda x %f | y %f\n", door->initial_dda->x, door->initial_dda->y);

	// }
	// else if ((*door->status) == OPENING)
	// {
	// 	printf("timer in opening %f\n", (*door->timer));
	// }
}

// static void	equation_straight_line(t_rc *rc, t_ray *ray, double curr_dda, int dir)
// {
// 	if (dir == VERTICAL)
// 	{
// 		ray->distance = (curr_dda - rc->player.d_coords.y) / ray->ray_vector.y;
// 		ray->hit_point.x = rc->player.d_coords.x + (ray->distance * ray->ray_vector.x);
// 		ray->hit_point.y = curr_dda;
// 	}
// 	else if (dir == HORIZONTAL)
// 	{
// 		ray->distance = (curr_dda - rc->player.d_coords.x) / ray->ray_vector.x;
// 		ray->hit_point.y = rc->player.d_coords.y + (ray->distance * ray->ray_vector.y);
// 		ray->hit_point.x = curr_dda;
// 	}
// }

static void	init_door(t_cub3D *data, t_door *d, t_vec2D *curr_dda)
{
	d->orientation_hit = -1;
	d->type_door = data->map.map[(int)curr_dda->y][(int)curr_dda->x];
	d->status = &data->map.door_state_map[(int)curr_dda->y][(int)curr_dda->x];
	d->timer = &data->map.timer_map[(int)curr_dda->y][(int)curr_dda->x];
	d->initial_dda = curr_dda;
}

int	handle_door_hit(t_cub3D *data, t_ray *ray, t_vec2D *curr_dda)
{
	t_door	door;

	init_door(data, &door, curr_dda);
	if (ray->distance < 1.0)
	{
		// printf("hit point ray x %f | y %f\n", ray->hit_point.x, ray->hit_point.y);
		// draw_square_point(data, ray->hit_point);
		if (data->rc.doors)
		{
			if ((*door.status) == CLOSED)
			{
				// Si esta closed, pasamos a estado opening
				(*door.status) = OPENING;
				door.timer_direction = 1.0;
				printf("status in array debe ser 1 %d\n", data->map.door_state_map[(int)curr_dda->y][(int)curr_dda->x]);
				// data->map.door_state_map[(int)curr_dda->y][(int)curr_dda->x] = 1;
			}
			else if ((*door.status) == OPEN)
			{
				(*door.status) = CLOSING;
				door.timer_direction = 0.0;
				// Si esta open, pasamos a estado closing
				printf("status in array deber ser 3 %d\n", data->map.door_state_map[(int)curr_dda->y][(int)curr_dda->x]);
			}
			data->rc.doors = 0;
		}
	}
	get_next_hit(data, ray, &door);
	return (1);
}