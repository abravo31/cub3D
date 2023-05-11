#include "../../includes/cub3D_struct.h"

static int	key_hook_player(int key_code, t_cub3D *data)
{
	if (key_code == MOVE_LEFT)
		data->rc.player.d_coords.x -= 0.1;
	else if (key_code == MOVE_RIGTH)
		data->rc.player.d_coords.x += 0.1;
	else if (key_code == MOVE_FORWARD)
		data->rc.player.d_coords.y -= 0.1;
	else if (key_code == MOVE_BACKWARD)
		data->rc.player.d_coords.y += 0.1;
	else if (key_code == ROTATE_LEFT)
	{
		data->rc.angle_direction -= 15;
		if (data->rc.angle_direction < 0)
			data->rc.angle_direction += 360;
	}
	else if (key_code == ROTATE_RIGTH)
	{
		data->rc.angle_direction += 15;
		if (data->rc.angle_direction > 360)
			data->rc.angle_direction -= 360;
	}
	else if (key_code == ESCAPE)
		ft_exit(data);
	else
		return (1); // bug
	render(data);
	return (0);
}

void	setup_controls_hooks(t_cub3D *data)
{
	mlx_key_hook(data->mlx_win, &key_hook_player, data);
	mlx_hook(data->mlx_win, 17, 0, ft_exit, data);
}