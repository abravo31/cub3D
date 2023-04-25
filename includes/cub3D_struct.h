#ifndef CUB3D_STRUCT_H
# define CUB3D_STRUCT_H

# include "../libft/includes/libft.h"
# include <stdio.h>
 #include <stdlib.h>
# define BUFFER_SIZE 42

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


typedef struct cub3D
{
    int     NO;
    int     SE;
    int     WE;
    int     EA;
    int     F;
    int     C;
    int     Y;
    char    *parsing_error;
    t_list  *ident_FC;
    t_list  *ident_coord;
    t_list  *map_list;
}   t_cub3D;

int	    get_list(t_cub3D *data, char *line);
void    __debug_parsing(t_cub3D *data);
void    ft_exit_and_free(t_cub3D *data, int ret);

#endif