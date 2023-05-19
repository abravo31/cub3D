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

static t_vec2D	move_for_back_ward(t_cub3D *data, int flag)
{
	t_vec2D	new_position_player;
	int		square_value;

	if (flag == MOVE_FORWARD)
	{
		new_position_player = scalar_mult(data->rc.dir_vec, 0.2);
		new_position_player = add_2D_vec(data->rc.player.d_coords, new_position_player);
		// printf("position player x %f | y %f\n", data->rc.player.d_coords.x, data->rc.player.d_coords.y);
		// printf("here : %d\n", data->map.map[(int)new_position_player.y][(int)new_position_player.x]);
	}
	else if (flag == MOVE_BACKWARD)
	{
		new_position_player = scalar_mult(data->rc.dir_vec, -0.2);
		new_position_player = add_2D_vec(data->rc.player.d_coords, new_position_player);
	}
	square_value = data->map.map[(int)new_position_player.y][(int)new_position_player.x];
	// printf("x %f | y %f\n", new_position_player.x, new_position_player.y);
	if (square_value >= 1 && square_value <= 2)
		return (data->rc.player.d_coords);
	return (new_position_player);
}

static t_vec2D	move_left_rigth(t_cub3D *data, int flag)
{
	t_vec2D	new_position_player;
	int		square_value;

	if (flag == MOVE_LEFT)
	{
		new_position_player = scalar_mult(data->rc.per_vec, 0.2);
		new_position_player = add_2D_vec(data->rc.player.d_coords, new_position_player);
	}
	else if (flag == MOVE_RIGTH)
	{
		new_position_player = scalar_mult(data->rc.per_vec, -0.2);
		new_position_player = add_2D_vec(data->rc.player.d_coords, new_position_player);
	}
	square_value = data->map.map[(int)new_position_player.y][(int)new_position_player.x];
	// printf("x %f | y %f\n", new_position_player.x, new_position_player.y);
	if (square_value >= 1 && square_value <= 2)
		return (data->rc.player.d_coords);
	return (new_position_player);
}


static int	key_hook_player(int key_code, t_cub3D *data)
{
	if (key_code == MOVE_LEFT)
		return (data->rc.player.d_coords = \
		move_left_rigth(data, MOVE_LEFT), render(data), 0);
	else if (key_code == MOVE_RIGTH)
		return (data->rc.player.d_coords = \
		move_left_rigth(data, MOVE_RIGTH), render(data), 0);
	else if (key_code == MOVE_FORWARD)
		return (data->rc.player.d_coords = \
		move_for_back_ward(data, MOVE_FORWARD), render(data), 0);
	else if (key_code == MOVE_BACKWARD)
		return (data->rc.player.d_coords = \
		move_for_back_ward(data, MOVE_BACKWARD), render(data), 0);
	else if (key_code == ROTATE_LEFT)
		return (ft_rotate_dir_vec(data, 1), render(data), 0);
	else if (key_code == ROTATE_RIGTH)
		return (ft_rotate_dir_vec(data, 2), render(data), 0);
	else if (key_code == ESCAPE)
		return (ft_exit(data), 0);
		// ft_exit_and_free(data, 0, NULL, NULL);
	// POR QUE ?
	// else
	// 	return (1);
	return (0);
}

void	setup_controls_hooks(t_cub3D *data)
{
	// mlx_key_hook(data->mlx_win, &key_hook_player, data);
	mlx_hook(data->mlx_win, 2, 1, &key_hook_player, data);
	mlx_hook(data->mlx_win, 17, 0, ft_exit, data);
}