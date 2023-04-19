#include "../../includes/cub3D_struct.h"

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		if (check_file_arg(argv[1]))
			return (1);
	}
	else
		return (printf("Invalid number of arguments\n"), 1);
	return (0);
}