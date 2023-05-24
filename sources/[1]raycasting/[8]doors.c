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
			printf("hit point x %f | y %f\n", ray->hit_point.x, ray->hit_point.y);
			draw_square_point(data, ray->hit_point);
			orientation_wall_hit = 1;
		}
	}
	if (orientation_wall_hit == -1)
	{
		printf("Entramos a este caso\n");
		equation_straight_line(rc, ray, door->next_dda.x, HORIZONTAL);
		printf("hit point x %f | y %f\n", ray->hit_point.x, ray->hit_point.y);
		if (!((ray->hit_point.y < door->initial_dda->y) || (ray->hit_point.x > (door->initial_dda->y + 1))))
		{
			printf("hit point x %f | y %f\n", ray->hit_point.x, ray->hit_point.y);
			draw_square_point(data, ray->hit_point);
			orientation_wall_hit = 1;
		}
	}
}

static void	next_point_hit_vertical(t_cub3D *data, t_rc *rc, t_ray *ray, t_door *door, int dir)
{
	int	orientation_wall_hit;

	orientation_wall_hit = -1;
	if (ray->is_facing_rigth || ray->is_facing_left)
	{
		equation_straight_line(rc, ray, door->next_dda.x, HORIZONTAL);
		if (!((ray->hit_point.y < door->initial_dda->y) || (ray->hit_point.y > (door->initial_dda->y + 1))))
		{
			printf("hit point x %f | y %f\n", ray->hit_point.x, ray->hit_point.y);
			draw_square_point(data, ray->hit_point);
			orientation_wall_hit = 1;
		}
	}
	if (orientation_wall_hit == -1)
	{
		printf("Entramos a este caso\n");
		equation_straight_line(rc, ray, door->next_dda.y, VERTICAL);
		printf("hit point x %f | y %f\n", ray->hit_point.x, ray->hit_point.y);
		if (!((ray->hit_point.x < door->initial_dda->x) || (ray->hit_point.x > (door->initial_dda->x + 1))))
		{
			printf("hit point x %f | y %f\n", ray->hit_point.x, ray->hit_point.y);
			draw_square_point(data, ray->hit_point);
			orientation_wall_hit = 1;
		}
	}
}

static void	get_next_hit(t_cub3D *data, t_ray *ray, t_door *door)
{
	t_vec2D	next_dda;

	printf("initial dda x %f | y %f\n", door->initial_dda->x, door->initial_dda->y);
	if (door->type_door == HORIZONTAL_DOOR)
	{
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
		// printf("Debo buscar el siguiente punto en y\n");
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
		next_point_hit_vertical(data, &data->rc, ray, door, VERTICAL);
	}
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

void    handle_door_hit(t_cub3D *data, t_ray *ray, t_vec2D *curr_dda)
{
	t_door	door;

	door.type_door = data->map.map[(int)curr_dda->y][(int)curr_dda->x];
	door.status = &data->map.door_state_map[(int)curr_dda->y][(int)curr_dda->x];
	door.timer = &data->map.timer_map[(int)curr_dda->y][(int)curr_dda->x];
	door.initial_dda = curr_dda;
	if (ray->distance < 1.0)
	{
		// printf("hit point ray x %f | y %f\n", ray->hit_point.x, ray->hit_point.y);
		// draw_square_point(data, ray->hit_point);
		if (data->rc.doors)
		{
			if ((*door.status) == 0)
			{
				// Si esta closed, pasamos a estado opening
				(*door.status) = 1;
				printf("status in array debe ser 1 %d\n", data->map.door_state_map[(int)curr_dda->y][(int)curr_dda->x]);
				// data->map.door_state_map[(int)curr_dda->y][(int)curr_dda->x] = 1;
			}
			else if ((*door.status) == 2)
			{
				(*door.status) = 3;
				// Si esta open, pasamos a estado closing
					printf("status in array deber ser 3 %d\n", data->map.door_state_map[(int)curr_dda->y][(int)curr_dda->x]);
			}
			data->rc.doors = 0;
		}
	}
	get_next_hit(data, ray, &door);
}