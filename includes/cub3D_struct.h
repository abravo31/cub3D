#ifndef CUB3D_STRUCT_H
# define CUB3D_STRUCT_H

# include "../libft/includes/libft.h"
# include "./parsing.h"
# include <stdio.h>

typedef enum ident_type
{
    NO,
    SE,
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
}   ident_coord;


typedef struct map_list
{
    char    *line;
    int     index;
}   t_map_list;

typedef struct cub3D
{
    t_list  *ident_FC;
    t_list  *ident_coord;
    t_list  *map_list;
}   t_Cub3D;

#endif