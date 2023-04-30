/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]parsing_identifier_coord.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo <abravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 19:20:31 by abravo            #+#    #+#             */
/*   Updated: 2023/04/30 21:15:24 by abravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_struct.h"

int	check_path_format(char *path)
{
	if (!ft_strcmp(&path[ft_strlen_int(path) - 4], ".xpm"))
		return (1);
	return (0);
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

t_coord	*new_coord(char *path, t_ident_type id)
{
	t_coord	*elem;
	int		j;
	int		k;

	j = 0;
	k = 0;
	elem = malloc(sizeof(t_coord));
	if (!elem)
		return (NULL);
	elem->path = path;
	elem->id = id;
	return (elem);
}

t_ident_type	eval_ident_coord_bis(char *ident, t_cub3D *data)
{
	if (is_identical("WE", ident))
	{
		if (data->WE == 0)
		{
			data->WE = 1;
			return (WE);
		}
	}
	else if (is_identical("EA", ident))
	{
		if (data->EA == 0)
		{
			data->EA = 1;
			return (EA);
		}
	}
	return (UNASSIGNED);
}

// Function to return corresponding token from string
t_ident_type	eval_ident_coord(char *ident, t_cub3D *data)
{
	if (is_identical("NO", ident))
	{
		if (data->NO == 0)
		{
			data->NO = 1;
			return (NO);
		}	
	}
	else if (is_identical("SO", ident))
	{
		if (data->SO == 0)
		{
			data->SO = 1;
			return (SO);
		}	
	}
	else if (is_identical("WE", ident))
		return (eval_ident_coord_bis(ident, data));
	else if (is_identical("EA", ident))
		return (eval_ident_coord_bis(ident, data));
	return (UNASSIGNED);
}
