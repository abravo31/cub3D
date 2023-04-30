#include "../../includes/cub3D_struct.h"

static int	ft_little_check(char *map_name)
{
	int	last_index;

	last_index = ft_strlen_int(map_name) - 1;
	if (map_name[last_index] == '/')
	{
		printf("You probably aren't launching the program ");
		printf("with a file\n");
		return (0);
	}
	return (1);
}

int	check_file_args(char *arg_file_name)
{
	ft_little_check(arg_file_name);
	return (0);
}