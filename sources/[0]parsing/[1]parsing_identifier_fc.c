/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]parsing_identifier_fc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo <abravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 19:20:31 by abravo            #+#    #+#             */
/*   Updated: 2023/04/30 21:05:47 by abravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_struct.h"

int	ft_atoi_fc(const char *str)
{
	int	res;
	int	i;

	if (!str)
		return (0);
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '\n' || !str[i])
		return (256);
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	while (str[i] && (str[i] == ' ' || str[i] == '\n'))
		i++;
	if (str[i])
		res = 256;
	return (res);
}

int	fill_rgb(t_fc *temp, char *color)
{
	if (!color)
		return (2);
	if (color && temp->R < 0)
		temp->R = ft_atoi_fc(color);
	else if (temp->R >= 0 && color && temp->G < 0)
		temp->G = ft_atoi_fc(color);
	else if (temp->R >= 0 && temp->G >= 0 && color && temp->B < 0)
		temp->B = ft_atoi_fc(color);
	return (0);
}

int	get_new_fc_colors(t_fc *temp, char *line, int i, char *color)
{
	while (line[i])
	{
		color = NULL;
		while (line[i] != ',' && line[i] != '\n')
		{
			if (get_char(line[i++], &color))
				return (1);
		}
		if (fill_rgb(temp, color))
			return (2);
		free(color);
		if (temp->B >= 0)
			break ;
		i++;
	}
	while (line[i++])
	{
		if (line[i] && line[i] != ' ' && line[i] != '\n')
			return (2);
	}
	if (temp->R < 0 || temp->R > 255 || temp->G < 0
		|| temp->G > 255 || temp->B < 0 || temp->B > 255)
		return (2);
	return (0);
}

t_fc	*new_fc(t_fc *temp, t_ident_type id)
{
	t_fc	*elem;

	elem = malloc(sizeof(t_fc));
	if (!elem)
		return (NULL);
	elem->R = temp->R;
	elem->G = temp->G;
	elem->B = temp->B;
	elem->id = id;
	return (elem);
}

t_ident_type	eval_ident_fc(char *ident, t_cub3D *data)
{
	if (is_identical("F", ident))
	{
		if (data->F == 0)
		{
			data->F = 1;
			return (F);
		}	
	}
	else if (is_identical("C", ident))
	{
		if (data->C == 0)
		{
			data->C = 1;
			return (C);
		}	
	}
	return (UNASSIGNED);
}
