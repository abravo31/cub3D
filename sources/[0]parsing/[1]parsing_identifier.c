#include "../../includes/cub3D_struct.h"

void	get_char(char c, char **str)
{
	char	*tmp;

	if (!*str)
	{
		*str = ft_strdup("?");
		// *str = malloc(sizeof(char) * 2);
		if (!*str)
		{
			*str = NULL; 
			printf("Malloc failed\n"); //checker
		}
		*str[0] = c;
		// *str[1] = '\0';
		return ;
	}
	tmp = ft_strjoin(*str, "?");
	free(*str);
	if (!tmp)
	{
		*str = NULL;
		printf("Malloc failed\n"); //checker
	}
	tmp[ft_strlen(tmp) - 1] = c;
	*str = tmp;
}

int	check_path_format(char *path)
{
	//printf("%s\n", &path[ft_strlen_int(path) - 4]);
	if (!ft_strcmp(&path[ft_strlen_int(path) - 4], ".xpm"))
		return (1);
	return (0);
}

//IMPORTANT check malloc failed
t_ident_coord	*new_coord(t_ident_type id, char *line, int i)
{
	t_ident_coord	*elem;
	int				j;
	int				k;

	elem = malloc(sizeof(t_ident_coord));
	if (!elem)
		printf("Malloc failed\n"); // gerer le retour et la memoire
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
		printf("Error path identifier\n"); // gerer le retour et la memoire
	elem->path = ft_strdup_i(&line[++j], --k);
	if (!elem->path) // gerer le retour et la memoire
		printf("Malloc failed\n"); 
	if (!check_path_format(elem->path)) // gerer le retour et la memoire
		printf("Error path format identifier\n");
	elem->id = id;
	return (elem);
}

int	ft_atoi_FC(const char *str)
{
	int	res;
	int	i;

	if (!str)
		return (0);
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	while(str[i] && (str[i] == ' ' || str[i] == '\n'))
		i++;
	if (str[i])
		res = 256;
	return (res);
}

t_ident_FC	*new_FC(t_ident_type id, char *line, int i)
{
	t_ident_FC	*elem;
	char 		*color;

	elem = malloc(sizeof(t_ident_FC));
	if (!elem)
		printf("Malloc failed\n");// gerer le retour et la memoire
	elem->R = -1;
	elem->G = -1;
	elem->B = -1;
	while (line[i])
	{
		color = NULL;
		while (line[i] != ',' && line[i] != '\n')
			get_char(line[i++], &color);
		if (!color)
			printf("error format RGB1\n");
		if (color && elem->R < 0)
			elem->R = ft_atoi_FC(color);
		else if (elem->R >= 0 && color && elem->G < 0)
			elem->G = ft_atoi_FC(color);
		else if (elem->R >= 0 && elem->G >= 0 && color && elem->B < 0)
			elem->B = ft_atoi_FC(color);
		free(color);
		if (elem->B >= 0)
			break;
		i++;
	}

	while (line[i])
	{
		if (line[i] && line[i] != ' ' && line[i] != '\n')
		{
			printf("erreur format RGB2\n");
			// fonction qui mettre l'erreur dans check_parsing_error 
			break; //il faut exit et liberer la memoire
		}
		i++;
	}
	if (elem->R < 0 || elem->R > 255 || elem->G < 0 || elem->G > 255 || elem->B < 0 || elem->B > 255)	
		printf("error F or C format\n"); // gerer le retour et la memoire
	elem->id = id;
	return (elem);
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
		if (data->SE == 0)
		{
			data->SE = 1;
			return (SO);
		}	
	}
	else if (is_identical("WE", ident))
		return (eval_ident_coord_bis(ident, data));
	else if (is_identical("EA", ident))
		return (eval_ident_coord_bis(ident, data));
	return (UNASSIGNED);
}

t_ident_type	eval_ident_FC(char *ident, t_cub3D *data)
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

int		handle_new_coord(t_cub3D *data, t_ident_type tmp, char *line, int i)
{
	t_ident_coord	*new_coord_node;

	new_coord_node = new_coord(tmp, line, i);
	if (!new_coord_node)
		return (1);
	if (generic_lst_add_node(&data->ident_coord, (void *)new_coord_node, sizeof(t_ident_coord)))
	{
		free (new_coord_node);
		return (1);
	}
	free (new_coord_node);
	return (0);
}

int		handle_new_FC(t_cub3D *data, t_ident_type tmp, char *line, int i)
{
	t_ident_FC	*new_FC_node;

	new_FC_node = new_FC(tmp, line, i);
	if (!new_FC_node)
		return (1);
	if (generic_lst_add_node(&data->ident_FC, (void *)new_FC_node, sizeof(t_ident_FC)))
	{
		free (new_FC_node);
		return (1);
	}
	free (new_FC_node);
	return (0);
}

t_map_list	*new_map_list(char *line, int y)
{
	t_map_list	*elem;

	elem = malloc(sizeof(t_map_list));
	if (!elem)
		return (NULL);
	elem->line = ft_strdup(line);
	if (!elem->line)
	{
		free (elem);
		return (NULL);
	}
	elem->_y = y;
	// Creo que aqui habria que cambiarlo por la funcion until_new_line
	elem->_x = ft_strlen(line);
	return(elem);
}

int		handle_new_line_map(t_cub3D *data, char *line, int y)
{
	t_map_list	*new_line_node;

	new_line_node = new_map_list(line, y);
	if (!new_line_node)
		return (1);
	if (generic_lst_add_node(&data->map_list, (void *)new_line_node, sizeof(t_map_list)))
	{
		free (new_line_node);
		return (1);
	}
	free (new_line_node);
	return (0);
}

void	delimitor(char **str, t_cub3D *data, char *line, int i)
{
	t_ident_type	tmp;

	tmp = 0;
	if ((tmp = eval_ident_coord(*str, data)) != 0)
	{
		if (handle_new_coord(data, tmp, line, i))
		{
			free (line);
			ft_exit_and_free(data, 1, str, MALLOC_FAIL);
		}
	}
	else if ((tmp = eval_ident_FC(*str, data)) != 0)
	{
		if (handle_new_FC(data, tmp, line, i))
		{
			free (line);
			ft_exit_and_free(data, 1, str, MALLOC_FAIL);
		}
	}
}

int	check_full_identifier(t_cub3D *data)
{
	int check;

	check = data->NO + data->SE + data->WE + data->EA + data->F + data->C;
	if (check > 0)
		return (check);
	return (0);
}


void	ft_free_FC(void *content)
{
	free(content);
}

void	ft_free_coord(void *content)
{
	t_ident_coord *tmp;

	tmp = (t_ident_coord *)content;
	free(tmp->path);
	free(tmp);
}

void ft_free_map_list(void *content)
{
	t_map_list *tmp;

	tmp = (t_map_list *)content;
	free(tmp->line);
	free(tmp);
}

void ft_exit_and_free(t_cub3D *data, int ret, char **str, char *error_msg)
{
	printf("Free..\n");
	if (error_msg)
		printf("%s\n", error_msg);
	if (str)
		free (*str);
	if (data->ident_coord)
	{
		printf("Here ident lcoord\n");
		ft_lstclear(&data->ident_coord, &ft_free_coord);
	}
	if (data->ident_FC)
	{
		printf("Here ident list\n");
		ft_lstclear(&data->ident_FC, &ft_free_FC);
	}
	if (data->map_list)
	{
		printf("Here map list\n");
		ft_lstclear(&data->map_list, &ft_free_map_list);
	}	
	exit(ret);
}

// void	check_parsing_error(t_cub3D *data)
// {
// 	if (data->parsing_error)
// 	{
// 		printf("%s\n", data->parsing_error);
// 		ft_exit_and_free(data, 1);
// 	}
// }

void	iter_line(t_cub3D *data, char **str, int i, char *line)
{
	// t_list	*new;

	if (check_full_identifier(data) < 6)
		while (line[++i])
		{
			if (line[i] == ' ' && line[i] != '\n' && line[i])
				delimitor(str, data, line, i);
			else if (line[i] != ' ' && line[i])
			{
				get_char(line[i], str);
				if (!*str)
				{
					ft_exit_and_free(data, 1, &line, MALLOC_FAIL);
				}
			}
		}
	else if (check_full_identifier(data) == 6)
	{
		data->Y = data->Y + 1;
		if (handle_new_line_map(data, line, data->Y))
		{
			ft_exit_and_free(data, 1, &line, MALLOC_FAIL);
		}	
	}
	free(*str);
}

// Function to parse the file map in a liked list
int	get_list(t_cub3D *data, char *line)
{
	int		i;
	char	*str;	

	i = -1;
	str = NULL;
	iter_line(data, &str, i, line);
	return (0);
}

// Function to check if the likeds list are created
void __debug_parsing(t_cub3D *data)
{
    t_list *iter = data->ident_coord;
    t_ident_coord  *current = NULL;
    while (iter)
    {
        current = (t_ident_coord*) iter->content;
        printf("{%d}[%s]\n", current->id, current->path);
        iter = iter->next;
    }

	t_list *iter2 = data->ident_FC;
    t_ident_FC  *current2 = NULL;
    while (iter2)
    {
        current2 = (t_ident_FC*) iter2->content;
        printf("{%d}(%d)(%d)(%d)\n", current2->id, current2->R, current2->G, current2->B);
        iter2 = iter2->next;
    }

	t_list *iter3 = data->map_list;
    t_map_list  *current3 = NULL;
    while (iter3)
    {
        current3 = (t_map_list*) iter3->content;
        printf("{%s}(%d)[%d]\n", current3->line, current3->_y, current3->_x);
        iter3 = iter3->next;
    }
}