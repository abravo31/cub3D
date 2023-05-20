#include "../../includes/cub3D_struct.h"

// static void	ft_clear_img(t_cub3D *data)
// {
// 	ft_bzero(data->img.addr, data->win_x * data->win_y * (data->img.bbp / 8));
// }

void	render(t_cub3D *data)
{
	// ft_clear_img(data);
	raycasting(data);
	// draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
}

int	lauch_raycasting(t_cub3D *data)
{
	if (setup_mlx_env(data))
		return (ft_exit_and_free(data, 1, NULL, MLX_ERROR), 1);
	ft_initialize_raycasting(data);
	data->background_colors[0] = find_color(data->ident_fc, F);
	data->background_colors[1] = find_color(data->ident_fc, C);
	data->wall_textures[0] = find_texture(data, data->ident_coord, NO);
	data->wall_textures[1] = find_texture(data, data->ident_coord, SO);
	data->wall_textures[2] = find_texture(data, data->ident_coord, WE);
	data->wall_textures[3] = find_texture(data, data->ident_coord, EA);
	render(data);
	setup_controls_hooks(data);
	mlx_loop(data->mlx);
	return (0);
}
