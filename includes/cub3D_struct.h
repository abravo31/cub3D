#ifndef CUB3D_STRUCT_H
# define CUB3D_STRUCT_H

# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
// # include "execution.h"
# include <stdio.h>

# define ARG_IS_DIR "You probably aren't launching the program with a file\n"
# define INVALID_EXTENSION "Provided file doesn't finish by .cub\n"
# define ERROR_OPEN_FD "Error opening the file, \
check if it exists or permissions\n"
# define INVALID_MAP "Invalid map\n"
# define MAP_IS_NOT_LAST_ELEM "The map is not the last element in the file\n"
# define INVALID_SYMBOL_MAP "The map contains invalid symbol\n"
# define DOUBLE_PLAYER "There's more than one player on the map\n"
# define MAP_UNCLOSED "The map isn't closed\n"
# define PLAYER_NONE "There is not player in map\n"
# define PLAYER_IN_EDGE "The player's in the edge\n"
# define INVALID_DOOR_POS "Invalid door's position\n"
# define PLAYER_CANT_MOVE "The player can't move in any direction\n"
# define MALLOC_FAIL "Malloc failed, exiting properly\n"
# define INVALID_PATH_TEXTURE "Error path identifier\n"
# define ERROR_RGB_FORMAT "Error format RGB\n"
# define IDENT_MISSING "Identifier missing\n"
# define IDENT_INVALID "Invalid identifier\n"
# define MLX_ERROR "Minilibx error initializing"

# define ESCAPE 65307
# define MOVE_FORWARD 119
# define MOVE_BACKWARD 115
# define MOVE_LEFT 97
# define MOVE_RIGTH 100
# define ROTATE_LEFT 65361
# define ROTATE_RIGTH 65363
# define N 1
# define S 2
# define E 3
# define W 4


typedef enum ident_type
{
	UNASSIGNED,
	NO,
	SO,
	WE,
	EA,
	F,
	C,
}	t_type;

typedef struct fc
{
	t_type	id;
	int		r;
	int		g;
	int		b;
}	t_fc;

typedef struct coord
{
	t_type	id;
	char	*path;
}	t_coord;

typedef struct map_list
{
	char	*line;
	int		_y;
	int		_x;
}	t_map_list;

typedef struct s_point
{
	int	x;
	int	y;
	int	color;
}		t_point;

typedef struct s_int_vec
{
	int	x;
	int	y;
}		t_int_vec;

typedef struct vector_2D
{
	double	x;
	double	y;
}			t_vec2D;


typedef struct player
{
	t_int_vec	i_coords;
	t_vec2D		d_coords;
	int			direction;
}			t_player;


typedef struct	player_position
{
	int		_is_set;
	int		_y;
	int		_x;
	int		_direction;
}			t_p_pos;

typedef struct line
{
	int		dx;
	int		dy;
	int		length;
	int		x1;
	int		y1;
	int		x2;
	int		y2;
	int		color;
}			t_line;

typedef struct map
{
	int			max_w;
	int			max_h;
	int			valide_map;
	int			b_idx;
	int			l_idx;
	t_p_pos		player;
	int			**map;
}				t_map;

typedef struct image
{
	void	*img;
	char	*addr;
	int		offset_window_x;
	int		offset_window_y;
	int		bpp;
	int		line_len;
	int		endian;
}			t_image;

typedef struct texture
{
	void	*img;
	char	*addr;
	int		img_width;
	int		img_height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_cam
{
	double		scale;
	double		fov;
}				t_cam;

typedef	struct	s_rc
{
	t_player	player;
	t_vec2D		dir_vec;
	t_vec2D		per_vec;
	t_vec2D		center_screen;
	double 		ray_dist;
	double		scale_map;
	double		fov;
}				t_rc;

typedef	struct	s_ray
{
	t_vec2D	ray_vector;
	double	distance;
	t_vec2D	hit_point;
	int		hit;
	int		hit_vertical;
	int		hit_horizontal;
	int		orientation_wall_hit;
	int		is_facing_down;
	int		is_facing_up;
	int		is_facing_rigth;
	int		is_facing_left;
}			t_ray;

typedef struct cub3D
{
	int			win_x;
	int			win_y;
	int			mid_x;
	int			mid_y;
	void		*mlx;
	void		*mlx_win;
	t_image		img;
	t_rc		rc;
	t_map		map;
	t_list		*ident_fc;
	t_list		*ident_coord;
	t_list		*map_list;
	t_texture	wall_textures[4];
	unsigned int background_colors[2];
	int			no;
	int			so;
	int			we;
	int			ea;
	int			f;
	int			c;
	int			y;
}	t_cub3D;

int		get_list(t_cub3D *data, char *line);
void	__debug_parsing(t_cub3D *data);
void	ft_exit_and_free(t_cub3D *data, int ret, char **str, char *error_msg);
int		check_full_identifier(t_cub3D *data);

/*Generic linked list*/
int		generic_lst_add_node(t_list **lst, void *data, size_t data_size);
t_list	*generic_get_node_by_idx(t_list **lst, int idx);

/*Debuging*/
void	print_coord_lst(t_list **begin_lst);
void	print_FC_lst(t_list **begin_lst);

/*Parsing utils*/
int		get_char(char c, char **str);
int		is_identical(char *s1, char *s2);
void	ft_free_map(t_map *map);
int		ft_read_file(t_list **lst, t_map *map);
int		ft_check_map(t_cub3D *data);
void	free_line_end_exit(char *line, t_cub3D *data, char **str, char *error);
int		ft_len_until_nl(char *s);
void	ft_free_fc(void *content);
void	ft_free_coord(void *content);
void	ft_free_map_list(void *content);

/*Identifier coord*/
int		get_new_coord_path(char **path, char *line, int i);
t_coord	*new_coord(char *path, t_type id);
t_type	eval_ident(char *ident, t_cub3D *data);

/*Identifier FC*/
int		get_new_fc_colors(t_fc *temp, char *line, int i, char *color);
t_fc	*new_fc(t_fc *temp, t_type id);
t_type	eval_ident_fc(char *ident, t_cub3D *data);

/*Identifier map*/
int		handle_new_line_map(t_cub3D *data, char *line, int y);

/*Parsing map*/
int		ft_check_map_lst(t_list **lst, t_map *map);
void	ft_free_map(t_map *map);
int		ft_get_map(t_list **lst, t_map *map);
int		ft_check_map(t_cub3D *data);
int		ft_check_player(t_map *map, int c_player, int y, int x);

/*Init raycasting*/
void    ft_initialize_raycasting(t_cub3D *data);
/*Init minilibx*/
int		ft_exit(t_cub3D *data);
int		setup_mlx_env(t_cub3D *data);
/*Minilibx utils*/
void	my_mlx_pixel_put(t_cub3D *data, t_point point);
void	ft_bresenham(t_cub3D *data, t_line *line);
void	ft_draw_line(t_cub3D *data, t_vec2D vec_1, t_vec2D vec_2, int color);
void	draw_square_point(t_cub3D *data, t_vec2D point);
/*Hooks*/
void	setup_controls_hooks(t_cub3D *data);
/************* Raycasting main functions**************/
int		lauch_raycasting(t_cub3D *data);
/*Raycasting*/
t_vec2D	ft_get_perpendicular_vec(t_vec2D dir_vec);
void    raycasting(t_cub3D *data);
/*DDA*/
void	wall_finder(t_cub3D *data, t_ray *ray, t_rc *rc);
void    dda_corners(int **map, t_ray *ray, t_vec2D *current_dda, int *hit);
/*Render*/
void	render(t_cub3D *data);
/*Scene*/
void	draw_square(t_cub3D *data, int y, int x, int obj, int square_size);
void	draw_scene(t_cub3D *data);
void	draw_scene_raycasting(t_cub3D *data);
/*Doors*/
void    handle_door_hit(t_cub3D *data, t_ray *ray, int x);
unsigned int	find_color(t_list	*ident_fc, int type);
t_texture	find_texture(t_cub3D *data, t_list	*ident_coord, int type);

/*Math utils*/
double	ft_deg_to_rad(double angle);
void	normalize_vector(t_vec2D *vector);
double	ft_abs_double(double n);
double	vec_cross_product(t_vec2D v1, t_vec2D v2);
t_vec2D	add_2D_vec(t_vec2D v1, t_vec2D v2);
t_vec2D subtract_2D_vec(t_vec2D v1, t_vec2D v2);
int		ft_abs_2_values(int a, int b);
t_vec2D	get_perpendicular_vec(t_vec2D vec);
t_vec2D	scalar_mult(t_vec2D vec, double scalar);
double	ft_abs_double(double n);
t_vec2D rotate_2D_vector(t_vec2D vec, int angle);
/*Execution*/
void	place_square(t_cub3D *data, t_point point, int square_size);
void	draw_minimap(t_cub3D *data);
void	draw_minimap_grid(t_cub3D *data);
void	draw_column(t_cub3D *data, t_ray *ray, int x);
#endif