#ifndef CUB3D_STRUCT_H
# define CUB3D_STRUCT_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# define BUFFER_SIZE 42

# define ARG_IS_DIR "You probably aren't launching the program with a file\n"
# define INVALID_EXTENSION "Provided file doesn't finish by .cub\n"
# define ERROR_OPEN_FD "Error opening the file, \
check if it exists or permissions\n"
# define INVALID_MAP "Invalid map\n"
# define MAP_IS_NOT_LAST_ELEM "The map is not the last element in the file\n"
# define DOUBLE_PLAYER "There's more than one player on the map\n"
# define MAP_UNCLOSED "The map isn't closed\n"
# define PLAYER_NONE "There is not player in map\n"
# define MALLOC_FAIL "Malloc failed, exiting properly\n"
# define INVALID_PATH_TEXTURE "Error path identifier\n"
# define ERROR_RGB_FORMAT "Error format RGB\n"
# define IDENT_MISSING "Identifier missing\n"
# define IDENT_INVALID "Invalid identifier\n"

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


typedef struct	player_position
{
	int		_is_set;
	int		_y;
	int		_x;
	int		_direction;
}			t_p_pos;

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

typedef struct cub3D
{
	int		no;
	int		so;
	int		we;
	int		ea;
	int		f;
	int		c;
	int		y;
	t_list	*ident_fc;
	t_list	*ident_coord;
	t_list	*map_list;
}	t_cub3D;

int		get_list(t_cub3D *data, char *line);
void	__debug_parsing(t_cub3D *data);
void	ft_exit_and_free(t_cub3D *data, int ret, char **str, char *error_msg);
int		check_full_identifier(t_cub3D *data);

/*Generic linked list*/
int		generic_lst_add_node(t_list **lst, void *data, size_t data_size);

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
int		ft_length_until_new_line(char *s);

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

//window

void	open_window(t_cub3D *data);

#endif