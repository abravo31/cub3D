#include "../../includes/cub3D_struct.h"

static int	ft_check_file_str(char *f_name)
{
	int	idx;
	int	length_f_name;

	length_f_name = ft_strlen_int(f_name);
	idx = ft_idx_last_occur_char(f_name, '/');
	if (idx >= 0 && f_name[idx] == '/' && (idx == (length_f_name - 1)))
		return(printf(ARG_IS_DIR), 1);
	idx = ft_idx_last_occur_char(f_name, '.');
	if (idx < 0 || ft_strncmp(f_name + idx, ".cub", ft_strlen_int(f_name + idx)))
		return (printf(INVALID_EXTENSION), 1);
	return (0);
}

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		if (ft_check_file_str(argv[1]))
			return (1);
	}
	else
		return (printf("Invalid number of arguments\n"), 1);
	return (0);
}