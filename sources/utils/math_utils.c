#include "../../includes/cub3D_struct.h"

double	ft_deg_to_rad(double angle)
{
	double	radians;

	radians = angle * (M_PI / 180);
	return (radians);
}

t_vec2D	add_2D_vec(t_vec2D v1, t_vec2D v2)
{
	t_vec2D	product_vector;

	product_vector.x = v1.x + v2.x;
	product_vector.y = v1.y + v2.y;
	return (product_vector);
}

int	ft_abs_2_values(int a, int b)
{
	if (a == b)
		return (0);
	else if (a < b)
		return (b - a);
	else
		return (a - b);
}