#include "../../includes/cub3D_struct.h"

static void	ft_rotate_dir_vec(t_cub3D *data, int rotation_direction)
{
	if (rotation_direction == 1)
	{
		// Rotation anticlockwise
		data->rc.dir_vec = rotate_2D_vector(data->rc.dir_vec, -15.0);
	}
	else if (rotation_direction == 2)
	{
		// Rotation clockwise
		data->rc.dir_vec= rotate_2D_vector(data->rc.dir_vec, 15.0);
	}
}

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
		ft_rotate_dir_vec(data, 1);
	else if (key_code == ROTATE_RIGTH)
		ft_rotate_dir_vec(data, 2);
	else if (key_code == ESCAPE)
		ft_exit(data);
	// POR QUE ?
	// else
	// 	return (1);
	render(data);
	return (0);
}

void	setup_controls_hooks(t_cub3D *data)
{
	mlx_key_hook(data->mlx_win, &key_hook_player, data);
	mlx_hook(data->mlx_win, 17, 0, ft_exit, data);
}