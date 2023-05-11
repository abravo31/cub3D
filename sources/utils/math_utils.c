#include "../../includes/cub3D_struct.h"

double	ft_deg_to_rad(double angle)
{
	double	radians;

	radians = angle * (M_PI / 180);
	return (radians);
}

// double normalize_angle(double angle)
// {
//     double	normalized_angle;

// 	normalized_angle = angle % (2 * M_PI);
//     if (normalized_angle < 0) {
//         normalized_angle = (2 * M_PI) + angle;
//     }
//     return normalized_angle;
// }

t_vec2D	add_2D_vec(t_vec2D v1, t_vec2D v2)
{
	t_vec2D	product_vector;

	product_vector.x = v1.x + v2.x;
	product_vector.y = v1.y + v2.y;
	return (product_vector);
}

t_vec2D subtract_2D_vec(t_vec2D v1, t_vec2D v2)
{
    t_vec2D result_vector;

    result_vector.x = v1.x - v2.x;
    result_vector.y = v1.y - v2.y;
    return result_vector;
}

t_vec2D	get_perpendicular_vec(t_vec2D vec)
{
	t_vec2D	perpendicular_vec;

	perpendicular_vec.x = vec.y;
	perpendicular_vec.y = vec.x;
	return (perpendicular_vec);
}

t_vec2D	scalar_mult(t_vec2D vec, double scalar)
{
	t_vec2D	res_scalar_product;

	res_scalar_product.x = vec.x * scalar;
	res_scalar_product.y = vec.y * scalar;
	return (res_scalar_product);
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