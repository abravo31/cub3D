#include "../../includes/cub3D_struct.h"

void	get_int_coords(t_player *player, t_vec2D *curr_dda)
{
	double		integer_value;
	double		double_value;

	double_value = modf(player->d_coords.x, &integer_value);
	player->i_coords.x = (int)integer_value;
	double_value = modf(player->d_coords.y, &integer_value);
	player->i_coords.y = (int)integer_value;
	(void)double_value;
	curr_dda->x = player->i_coords.x;
	curr_dda->y = player->i_coords.y;
}

void	equation_straight_line(t_rc *rc, t_ray *ray, double curr_dda, int dir)
{
	if (dir == VERTICAL)
	{
		ray->dist = (curr_dda - rc->player.d_coords.y) / ray->vec.y;
		ray->hit_point.x = rc->player.d_coords.x + (ray->dist * ray->vec.x);
		ray->hit_point.y = curr_dda;
	}
	else if (dir == HORIZONTAL)
	{
		ray->dist = (curr_dda - rc->player.d_coords.x) / ray->vec.x;
		ray->hit_point.y = rc->player.d_coords.y + (ray->dist * ray->vec.y);
		ray->hit_point.x = curr_dda;
	}
}