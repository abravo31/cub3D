#include "../../includes/cub3D_struct.h"

static void	ft_clear_img(t_cub3D *data)
{
	ft_bzero(data->img.addr, data->win_x * data->win_y  * data->img.bbp);
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
	setup_controls_hooks(data);
	render(data);
	mlx_loop(data->mlx);
	return (0);
}
