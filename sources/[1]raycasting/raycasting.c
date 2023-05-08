#include "../../includes/cub3D_struct.h"

static void	ft_clear_img(t_cub3D *data)
{
	ft_bzero(data->img.addr, data->win_x * data->win_y * (data->img.bbp / 8));
}

static void	ft_initialize_player(t_cub3D *data)
{
	data->player.i_coords.y = data->map.player._y;
	data->player.i_coords.x = data->map.player._x;
	data->player.i_coords.color = 0x00FF00;
	data->player.d_coords.y = (double)data->player.i_coords.y + 0.5;
	data->player.d_coords.x = (double)data->player.i_coords.x + 0.5;
	// printf("Initializing...\n");
	// printf("f y %f\n", data->player.d_coords.y);
	// printf("f x %f\n", data->player.d_coords.x);
	// printf("y: %d\n", data->player.i_coords.y);
	// printf("x :%d\n", data->player.i_coords.x);
}

void	render(t_cub3D *data)
{
	ft_clear_img(data);
	draw_scene(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
}

int	lauch_raycasting(t_cub3D *data)
{
	if (setup_mlx_env(data))
		return (ft_exit_and_free(data, 1, NULL, MLX_ERROR),1);
	ft_initialize_player(data);
	setup_controls_hooks(data);
	render(data);
	mlx_loop(data->mlx);
	return (0);
}
