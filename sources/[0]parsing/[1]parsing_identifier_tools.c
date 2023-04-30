/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   [1]parsing_identifier_tools.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abravo <abravo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 19:20:31 by abravo            #+#    #+#             */
/*   Updated: 2023/04/30 20:21:05 by abravo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_struct.h"

int	get_char(char c, char **str)
{
	char	*tmp;

	if (!*str)
	{
		*str = ft_strdup("?");
		if (!*str)
		{
			*str = NULL;
			return (1);
		}
		*str[0] = c;
		return (0);
	}
	tmp = ft_strjoin(*str, "?");
	free(*str);
	if (!tmp)
	{
		*str = NULL;
		return (1);
	}
	tmp[ft_strlen(tmp) - 1] = c;
	*str = tmp;
	return (0);
}

int	check_full_identifier(t_cub3D *data)
{
	int	check;

	check = data->NO + data->SO + data->WE + data->EA + data->F + data->C;
	if (check > 0)
		return (check);
	return (0);
}

int	is_identical(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] == '\0');
}
