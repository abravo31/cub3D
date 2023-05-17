#include "../../includes/cub3D_struct.h"

static int	corners_up_left(int **map, t_ray *ray, t_vec2D *current_dda)
{
    int y_dda;
    int x_dda;
    int hit;

    y_dda = (int)current_dda->y;
    x_dda = (int)current_dda->x;
    hit = 0;
    if (map[y_dda - 1][x_dda] == 1)
    {
        current_dda->y = current_dda->y - 1;
		ray->orientation_wall_hit = 1;
		hit = 1;
    }
    else if (map[y_dda][x_dda - 1] == 1)
    {
        current_dda->x = current_dda->x - 1;
		ray->orientation_wall_hit = 4;
        hit = 1;
    }
    else if (map[y_dda - 1][x_dda - 1] == 1)
    {
        current_dda->y = current_dda->y - 1;
        current_dda->x = current_dda->x - 1;
		ray->orientation_wall_hit = 5;
        hit = 1;
    }
    else
    {
        current_dda->y = current_dda->y - 1;
        current_dda->x = current_dda->x - 1;
        ray->orientation_wall_hit = -1;
    }
    return (hit);
}

static int	corners_up_rigth(int **map, t_ray *ray, t_vec2D *current_dda)
{
    int y_dda;
    int x_dda;
    int hit;

    y_dda = (int)current_dda->y;
    x_dda = (int)current_dda->x;
    hit = 0;
    if (map[y_dda - 1][x_dda] == 1)
    {
        current_dda->y = current_dda->y - 1;
		ray->orientation_wall_hit = 1;
		hit = 1;
    }
    else if (map[y_dda][x_dda + 1] == 1)
    {
        current_dda->x = current_dda->x + 1;
		ray->orientation_wall_hit = 3;
        hit = 1;
    }
    else if (map[y_dda - 1][x_dda + 1] == 1)
    {
        current_dda->y = current_dda->y - 1;
        current_dda->x = current_dda->x + 1;
		ray->orientation_wall_hit = 5;
        hit = 1;
    }
	else
	{
		current_dda->y = current_dda->y - 1;
        current_dda->x = current_dda->x + 1;
		ray->orientation_wall_hit = -1;
	}
    return (hit);
}

static int	corners_down_rigth(int **map, t_ray *ray, t_vec2D *current_dda)
{
    int y_dda;
    int x_dda;
    int hit;

    y_dda = (int)current_dda->y;
    x_dda = (int)current_dda->x;
    hit = 0;
    if (map[y_dda + 1][x_dda] == 1)
    {
        current_dda->y = current_dda->y + 1;
		ray->orientation_wall_hit = 2;
		hit = 1;
    }
    else if (map[y_dda][x_dda + 1] == 1)
    {
        current_dda->x = current_dda->x + 1;
		ray->orientation_wall_hit = 3;
        hit = 1;
    }
    else if (map[y_dda - 1][x_dda - 1] == 1)
    {
        current_dda->y = current_dda->y + 1;
        current_dda->x = current_dda->x + 1;
		ray->orientation_wall_hit = 5;
        hit = 1;
    }
    else
    {
        current_dda->y = current_dda->y + 1;
        current_dda->x = current_dda->x + 1;
		ray->orientation_wall_hit = -1;
    }
    return (hit);
}

static int	corners_down_left(int **map, t_ray *ray, t_vec2D *current_dda)
{
	int y_dda;
    int x_dda;
    int hit;

    y_dda = (int)current_dda->y;
    x_dda = (int)current_dda->x;
    hit = 0;
    if (map[y_dda + 1][x_dda] == 1)
    {
        current_dda->y = current_dda->y + 1;
		ray->orientation_wall_hit = 2;
		hit = 1;
    }
    else if (map[y_dda][x_dda - 1] == 1)
    {
        current_dda->x = current_dda->x - 1;
		ray->orientation_wall_hit = 4;
        hit = 1;
    }
    else if (map[y_dda + 1][x_dda - 1] == 1)
    {
        current_dda->y = current_dda->y + 1;
        current_dda->x = current_dda->x - 1;
		ray->orientation_wall_hit = 5;
        hit = 1;
    }
    else
    {
        current_dda->y = current_dda->y + 1;
        current_dda->x = current_dda->x - 1;
		ray->orientation_wall_hit = -1;
    }
    return (hit);
}

void    dda_corners(int **map, t_ray *ray, t_vec2D *current_dda, int *hit)
{
    if (ray->orientation_wall_hit == 5)
    {
        *hit = corners_up_rigth(map, ray, current_dda);
    }
    if (ray->orientation_wall_hit == 6)
    {
		*hit = corners_up_left(map, ray, current_dda);
	}
    if (ray->orientation_wall_hit == 7)
    {
        *hit = corners_down_rigth(map, ray, current_dda);
    }
    if (ray->orientation_wall_hit == 8)
    {
       *hit = corners_down_left(map, ray, current_dda);
    }
}
