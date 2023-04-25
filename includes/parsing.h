#ifndef PARSING_H
#define PARSING_H

/*Macros for the errors*/
#define ARG_IS_DIR "You probably aren't launching the program with a file\n"
#define INVALID_EXTENSION "Provided file doesn't finish by .cub\n"
#define ERROR_OPEN_FD "Error opening the file, check if it exists or permissions\n"
#define INVALID_MAP "Invalid map\n"
#define MAP_IS_NOT_LAST_ELEM "The map is not the last element in the file\n"

typedef struct map
{
	int			max_width;
	int			max_heigth;
	int			closed_map;
	int			begin_idx;
	int			**map;
}				t_map;


/*Parsing utils*/
void	ft_free_map(t_map *map);
int		ft_read_file(char *file_name, t_map *map);
int		ft_check_map(char *file_name);
#endif