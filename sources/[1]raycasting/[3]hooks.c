#include "../../includes/cub3D_struct.h"

static t_vec2D check_step(t_cub3D *data, int map_elem, t_vec2D new_pos)
{
	int		door_state;

	if (map_elem == 1  || (map_elem == 32))
		return (data->rc.player.d_coords);
	else if (map_elem == 2 || map_elem == 3)
	{
		door_state = data->map.door_state_map[(int)new_pos.y][(int)new_pos.x];
		printf("door state %d\n", door_state);
		if (door_state == CLOSED)
			return (data->rc.player.d_coords);
		else if (door_state == OPEN)
			return (new_pos);
	}
	return (new_pos);
}

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
	t_vec2D	n_pos;
	int		square_value;

	if (flag == MOVE_FORWARD)
	{
		n_pos = scalar_mult(data->rc.dir_vec, 0.2);
		n_pos = add_2D_vec(data->rc.player.d_coords, n_pos);
	}
	else if (flag == MOVE_BACKWARD)
	{
		n_pos = scalar_mult(data->rc.dir_vec, -0.2);
		n_pos = add_2D_vec(data->rc.player.d_coords, n_pos);
	}
	square_value = data->map.map[(int)n_pos.y][(int)n_pos.x];
	return (check_step(data, square_value, n_pos));
}

static t_vec2D	move_left_rigth(t_cub3D *data, int flag)
{
	t_vec2D	n_pos;
	int		square_value;

	if (flag == MOVE_LEFT)
	{
		n_pos = scalar_mult(data->rc.per_vec, 0.2);
		n_pos = add_2D_vec(data->rc.player.d_coords, n_pos);
	}
	else if (flag == MOVE_RIGTH)
	{
		n_pos = scalar_mult(data->rc.per_vec, -0.2);
		n_pos = add_2D_vec(data->rc.player.d_coords, n_pos);
	}
	square_value = data->map.map[(int)n_pos.y][(int)n_pos.x];
	return (check_step(data, square_value, n_pos));
}

static int	exec_hook(t_cub3D *data)
{
	if (data->events.move_left)
		data->rc.player.d_coords = move_left_rigth(data, MOVE_LEFT);
	if (data->events.move_rigth)
		data->rc.player.d_coords = move_left_rigth(data, MOVE_RIGTH);
	if (data->events.move_forward)
		data->rc.player.d_coords = move_for_back_ward(data, MOVE_FORWARD);
	if (data->events.move_backward)
		data->rc.player.d_coords = move_for_back_ward(data, MOVE_BACKWARD);
	if (data->events.rotate_left)
		ft_rotate_dir_vec(data, 1);
	if (data->events.rotate_rigth)
		ft_rotate_dir_vec(data, 2);
	render(data);
	return (0);
}

static int	desactive_hook(int key_code, t_cub3D *data)
{
	if (key_code == 32)
		data->rc.doors = 0;
	if (key_code == MOVE_LEFT)
		data->events.move_left = 0;
	else if (key_code == MOVE_RIGTH)
		data->events.move_rigth = 0;
	else if (key_code == MOVE_FORWARD)
		data->events.move_forward = 0;
	else if (key_code == MOVE_BACKWARD)
		data->events.move_backward = 0;
	else if (key_code == ROTATE_LEFT)
		data->events.rotate_left = 0;
	else if (key_code == ROTATE_RIGTH)
		data->events.rotate_rigth = 0;
	return (0);
}

static int	active_hook(int key_code, t_cub3D *data)
{
	if (key_code == 32)
	{
		data->rc.doors = 1;
	}
	if (key_code == MOVE_LEFT)
		data->events.move_left = 1;
	else if (key_code == MOVE_RIGTH)
		data->events.move_rigth = 1;
	else if (key_code == MOVE_FORWARD)
		data->events.move_forward = 1;
	else if (key_code == MOVE_BACKWARD)
		data->events.move_backward = 1;
	else if (key_code == ROTATE_LEFT)
		data->events.rotate_left = 1;
	else if (key_code == ROTATE_RIGTH)
		data->events.rotate_rigth = 1;
	else if (key_code == ESCAPE)
		return (ft_exit(data), 0);
	exec_hook(data);
	return (0);
}

void	setup_controls_hooks(t_cub3D *data)
{
	mlx_hook(data->mlx_win, 2, (1L<<0), active_hook, data);
	mlx_hook(data->mlx_win, 3, (1L<<1), desactive_hook, data);
	// mlx_hook(data->mlx_win, 4, (1L<<0), doors, data);
	// mlx_hook(data->mlx_win, 2, (1L<<0), exec_hook, data);
	mlx_hook(data->mlx_win, 17, 0, ft_exit, data);
}