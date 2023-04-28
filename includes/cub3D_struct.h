#ifndef CUB3D_STRUCT_H
# define CUB3D_STRUCT_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# define BUFFER_SIZE 42

#define ARG_IS_DIR "You probably aren't launching the program with a file\n"
#define INVALID_EXTENSION "Provided file doesn't finish by .cub\n"
#define ERROR_OPEN_FD "Error opening the file, check if it exists or permissions\n"
#define INVALID_MAP "Invalid map\n"
#define MAP_IS_NOT_LAST_ELEM "The map is not the last element in the file\n"
#define DOUBLE_PLAYER "There's more than one player on the map\n"
#define MAP_UNCLOSED "The map isn't closed\n"
#define PLAYER_NONE "There is not player in map\n"
#define MALLOC_FAIL "Malloc failed, exiting properly"
#define INVALID_PATH_TEXTURE "Error path identifier\n"
#define ERROR_RGB_FORMAT "Error format RGB\n"

typedef enum ident_type
{
    UNASSIGNED,
    NO,
    SO,
    WE,
    EA,
    F,
    C,
}   t_ident_type;

typedef struct ident_FC
{
    t_ident_type    id;
    int             R;
    int             G;
    int             B;
}   t_ident_FC;

typedef struct ident_coord
{
    t_ident_type    id;
    char            *path;
}   t_ident_coord;


typedef struct map_list
{
    char    *line;
    int     _y;
    int     _x;
}   t_map_list;


typedef	struct player_position
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
    int     NO;
    int     SO;
    int     WE;
    int     EA;
    int     F;
    int     C;
    int     Y;
    t_list  *ident_FC;
    t_list  *ident_coord;
    t_list  *map_list;
}   t_cub3D;

int	    get_list(t_cub3D *data, char *line);
void    __debug_parsing(t_cub3D *data);
void    ft_exit_and_free(t_cub3D *data, int ret, char **str, char *error_msg);
int	    check_full_identifier(t_cub3D *data);

/*Generic linked list*/
int     generic_lst_add_node(t_list **lst, void *data, size_t data_size);

/*Debuging*/
void    print_coord_lst(t_list **begin_lst);
void    print_FC_lst(t_list **begin_lst);

/*Parsing utils*/
void	ft_free_map(t_map *map);
int		ft_read_file(t_list **lst, t_map *map);
int		ft_check_map(t_cub3D *data);

#endif