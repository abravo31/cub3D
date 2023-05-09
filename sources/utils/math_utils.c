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

t_vec2D	get_perpendicular_vec(t_vec2D vec)
{
	t_vec2D	perpendicular_vec;

	perpendicular_vec.x = vec.y;
	perpendicular_vec.y = vec.x;
	return (perpendicular_vec);
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

double	ft_abs_double(double n)
{
	if (n < 0)
		return (-n);
	return (n);
}

t_vec2D rotate_2D_vector(t_vec2D vec, int angle)
{
	t_vec2D	rotate_vec;
	double	angle_radians;

	angle_radians = ft_deg_to_rad((double)angle);
	rotate_vec.x = (vec.x * cos(angle_radians)) - (vec.y * sin(angle_radians));
	rotate_vec.y = (vec.x * sin(angle_radians)) + (vec.y * cos(angle_radians));
	return (rotate_vec);
}