#include "../../includes/cub3D_struct.h"

static int	key_hook_player(int key_code, t_cub3D *data)
{
	printf("key code : %d\n", key_code);
	if (key_code == ROTATE_LEFT)
		data->map.player._x -= 1;
	// else if (key_code == ROTATE_RIGTH)
	// 	fdf->cam.angle_y_rot += 5;
	// else if (key_code == ROTATE_UP)
	// 	ft_scale_vertex(fdf, 1);
	// else if (key_code == ROTATE_DOWN)
	// 	ft_scale_vertex(fdf, 0);
	// else if (key_code == ZOOM_IN)
	// 	fdf->cam.scale += 2;
	if (key_code == ESCAPE)
		ft_exit(data);
	draw_scene(data);
	return (0);
}

void	setup_controls_hooks(t_cub3D *data)
{
	mlx_key_hook(data->mlx_win, &key_hook_player, data);
	mlx_hook(data->mlx_win, 17, 0, ft_exit, data);
}