# include "cub3D_struct.h"


int	ft_exit(t_cub3D *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(1);
}

void	setup_data_for_mlx(t_cub3D *data)
{
	data->win_x = 1920;
	data->win_y = 1080;
	data->mid_x = data->win_x / 2;
	data->mid_y = data->win_y / 2;
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, data->win_x, data->win_y, "FDF");
	data->img = mlx_new_image(data->mlx, data->win_x, data->win_y);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_len,
			&data->endian);
}

int	key_hook(int key, t_cub3D *data)
{
	if (key == 65307)
		ft_exit(data);
	return (0);
}

void	setup_controls(t_cub3D *data)
{
	mlx_hook(data->mlx_win, 2, 1, key_hook, data);
	mlx_hook(data->mlx_win, 17, 0, ft_exit, data);
}

void	open_window(t_cub3D *data)
{
	setup_controls(data);
	mlx_loop(data->mlx);
}
