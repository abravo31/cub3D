/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]parsing_identifier_coord.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo <abravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 19:20:31 by abravo            #+#    #+#             */
/*   Updated: 2023/05/20 17:31:13 by abravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_struct.h"

int	check_path_format(char *path)
{
	int	fd;

	if (ft_strcmp(&path[ft_strlen_int(path) - 4], ".xpm"))
		return (0);
	// printf("\n\n\n\n\nKHFJLD:JFKL:DSJ FKL:DSJFLK:SDJFKLH\n\n");
	fd = open(path, O_WRONLY);
	// printf("fd: %d, path: %s\n", fd, path);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	get_new_coord_path(char **path, char *line, int i)
{
	int		k;
	int		j;

	while (line[i] && line[i] == ' ')
		i++;
	j = i - 1;
	k = 0;
	while (line[i] && line[i] != ' ')
	{
		k++;
		i++;
	}	
	if (line[i] == ' ')
		return (2);
	*path = ft_strdup_i(&line[++j], --k);
	if (!*path)
		return (1);
	if (!check_path_format(*path))
		return (free(*path), 2);
	return (0);
}

t_coord	*new_coord(char *path, t_type id)
{
	t_coord	*elem;

	elem = malloc(sizeof(t_coord));
	if (!elem)
		return (NULL);
	elem->path = path;
	elem->id = id;
	return (elem);
}

t_type	eval_ident_coord_bis(char *ident, t_cub3D *data)
{
	if (is_identical("WE", ident))
	{
		if (data->we == 0)
		{
			data->we = 1;
			return (WE);
		}
		return (7);
	}
	else if (is_identical("EA", ident))
	{
		if (data->ea == 0)
		{
			data->ea = 1;
			return (EA);
		}
		return (7);
	}
	return (UNASSIGNED);
}

t_type	eval_ident_coord(char *ident, t_cub3D *data)
{
	if (is_identical("NO", ident))
	{
		if (data->no == 0)
		{
			data->no = 1;
			return (NO);
		}
		return (7);
	}
	else if (is_identical("SO", ident))
	{
		if (data->so == 0)
		{
			data->so = 1;
			return (SO);
		}
		return (7);
	}
	return (UNASSIGNED);
}

// Function to return corresponding token from string
t_type	eval_ident(char *ident, t_cub3D *data)
{
	if (is_identical("NO", ident))
		return (eval_ident_coord(ident, data));
	else if (is_identical("SO", ident))
		return (eval_ident_coord(ident, data));
	else if (is_identical("WE", ident))
		return (eval_ident_coord_bis(ident, data));
	else if (is_identical("EA", ident))
		return (eval_ident_coord_bis(ident, data));
	else if (is_identical("F", ident))
		return (eval_ident_fc(ident, data));
	else if (is_identical("C", ident))
		return (eval_ident_fc(ident, data));
	return (UNASSIGNED);
}
