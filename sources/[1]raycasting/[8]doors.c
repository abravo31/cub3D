#include "../../includes/cub3D_struct.h"

void    handle_door_hit(t_cub3D *data, t_ray *ray, int x)
{
    (void)x;
    draw_square_point(data, ray->hit_point);
    printf("hit point ray (%d) x %f | y %f\n", x, ray->hit_point.x, ray->hit_point.y);
}