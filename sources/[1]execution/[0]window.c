#include "execution.h"

int	ft_exit(t_cub3D *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	if (data->ident_coord)
		ft_lstclear(&data->ident_coord, &ft_free_coord);
	if (data->ident_fc)
		ft_lstclear(&data->ident_fc, &ft_free_fc);
	ft_free_map(&data->map);
	exit(1);
}

void	setup_data_for_mlx(t_cub3D *data)
{
	data->win_x = 1200;
	data->win_y = 700;
	data->mid_x = data->win_x / 2;
	data->mid_y = data->win_y / 2;
	data->fov = ft_deg_to_rad(60.0);
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, data->win_x, data->win_y, "cub3D");
	data->img = mlx_new_image(data->mlx, data->win_x, data->win_y);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_len,
			&data->endian);
}

int	key_hook(int key, t_cub3D *data)
{
	mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, data->win_x, data->win_y);
	data->addr = mlx_get_data_addr(data->img,
			&(data->bpp), &(data->line_len), &(data->endian));
	printf("key: %d\n", key);
	if (key == 65307)
		ft_exit(data);
	// if (key == 32)
		// place_square(data, (t_point){300, 300, 0xFFF00FF}, 10);
		// my_mlx_pixel_put(data, (t_point){300, 300, 0xFFF00FF});
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	return (0);
}

void	setup_controls(t_cub3D *data)
{
	mlx_hook(data->mlx_win, 2, 1, key_hook, data);
	mlx_hook(data->mlx_win, 17, 0, ft_exit, data);
}

void	open_window(t_cub3D *data)
{
	setup_data_for_mlx(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	setup_controls(data);
	mlx_loop(data->mlx);
	// try_raycasting(data);
}
