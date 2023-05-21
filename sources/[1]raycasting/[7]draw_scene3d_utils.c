
#include "../../includes/cub3D_struct.h"

double	vec_length(t_vec2D vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y));
}

double	dot_prod(t_vec2D vec1, t_vec2D vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y);
}

int	color_from_texture(t_cub3D *data, int direction, double xpercent, int y)
{
	t_texture	texture;
	int			x;

	texture = data->wall_textures[direction - 1];
	if (y > texture.img_height)
		y = texture.img_height;
	if (y < 0)
		y = 0;
	x = texture.img_width * xpercent;
	if (x > texture.img_width)
		x = texture.img_width;
	if (x < 0)
		x = 0;
	return (((int *)texture.addr)[y * (texture.line_len / sizeof(int)) + x]);
}

int	color_from_texture_back(t_cub3D *data, double xpercent, double ypercent)
{
	t_texture	texture;
	int			x;
	int			y;

	texture = data->wall_textures[2];
	y = texture.img_height * ypercent;
	x = texture.img_width * xpercent;
	return (((int *)texture.addr)[y * (texture.line_len / sizeof(int)) + x]);
}
