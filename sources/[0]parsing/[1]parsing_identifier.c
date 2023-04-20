#include "../../includes/cub3D_struct.h"

void	get_char(char c, char **str)
{
	char	*tmp;

	if (!*str)
	{
		*str = ft_strdup("?");
		if (!*str)
		{
			*str = NULL; 
			printf("Malloc failed\n");
		}
			
		*str[0] = c;
		return ;
	}
	tmp = ft_strjoin(*str, "?");
	free(*str);
	if (!tmp)
	{
		*str = NULL;
		printf("Malloc failed\n");
	}
	tmp[ft_strlen(tmp) - 1] = c;
	*str = tmp;
}

//IMPORTANT check malloc failed
t_ident_coord	*new_coord(t_ident_type id, char *line, int i)
{
	t_ident_coord	*elem;
	int				j;

	j = 0;
	elem = malloc(sizeof(t_ident_coord));
	if (!elem)
		printf("Malloc failed\n"); // gerer le retour et la memoire
	while (line[i] == ' ' && line[i])
		i++;
	j = i;
	while (line[i] && line[i] != ' ')
		i++;
	if (line[i] == ' ')
		printf("Error path identifier\n"); // gerer le retour et la memoire
	elem->path = ft_strdup_i(line, j);
	elem->id = id;
	return (elem);
}

t_ident_FC	*new_FC(t_ident_type id, char *line, int i)
{
	t_ident_FC	*elem;
	char 		*color;

	elem = malloc(sizeof(t_ident_coord));
	if (!elem)
		printf("Malloc failed\n");// gerer le retour et la memoire
	elem->R = -1;
	elem->G = -1;
	elem->B = -1;
	while (line[i])
	{
		color = NULL;
		while (line[i] == ' ' && line[i] != '\n' && line[i])
			i++;
		while (line[i] >= '0' && line[i] <= '9')
			get_char(line[i++], &color);
		if (line[i] == ',' && elem->R < 0)
			elem->R = ft_atoi(color);
		else if (line[i] == ',' && elem->G < 0)
			elem->G = ft_atoi(color);
		else if (line[i] == '\n' && elem->B < 0)
			elem->B = ft_atoi(color);
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

int check_double(int empty)
{
	if (empty == 0)
		return (1);
	return (0); // peut-etre mettre l'erreur et free ici
}

// Function to return corresponding token from string
t_ident_type	eval_ident_coord(char *ident, t_cub3D *data)
{
	if (is_identical("NO", ident))
	{
		if (data->NO == check_double(data->NO))
			return (NO);
		else
			return (UNASSIGNED); //imprimer erreur et free tout qui a ete malloque avant
	}
	else if (is_identical("SE", ident))
	{
		if (data->SE == check_double(data->SE))
			return (SE);
		else
			return (UNASSIGNED); //imprimer erreur et free tout qui a ete malloque avant
	}
	else if (is_identical("WE", ident))
	{
		if (data->WE == check_double(data->WE))
			return (WE);
		else
			return (UNASSIGNED); //imprimer erreur et free tout qui a ete malloque avant
	}
	else if (is_identical("EA", ident))
	{
		if (data->EA == check_double(data->EA))
			return (EA);
		else
			return (UNASSIGNED);//imprimer erreur et free tout qui a ete malloque avant
	}
	return (UNASSIGNED);
}

t_ident_type	eval_ident_FC(char *ident, t_cub3D *data)
{
	if (is_identical("F", ident))
	{
		if (data->F == check_double(data->F))
			return (F);
		else
			return (UNASSIGNED); //imprimer erreur et free tout qui a ete malloque avant
	}
	else if (is_identical("C", ident))
	{
		if (data->C == check_double(data->C))
			return (C);
		else
			return (UNASSIGNED); //imprimer erreur et free tout qui a ete malloque avant
	}
	return (UNASSIGNED);
}

void	delimitor(char **str, t_cub3D *data, char *line, int i)
{
	t_list	*new;
	// int		check;

	if (!*str || data->parsing_error)
		return ;
	if (data->ident_coord == NULL && eval_ident_coord(*str, data))
	{
		data->ident_coord = ft_lstnew((void *)new_coord(eval_ident_coord(*str, data), line, i));
		if (!data->ident_coord)
			printf("Malloc failed, il faut gerer");
	}
	else if (data->ident_coord && eval_ident_coord(*str, data))
	{
		new = ft_lstnew((void *)new_coord(eval_ident_coord(*str, data), line, i));
		if (!new)
			printf("Malloc failed, il faut gerer");
		ft_lstadd_back(&data->ident_coord, new);
	}
	else if (data->ident_FC == NULL && eval_ident_FC(*str, data))
	{
		data->ident_FC = ft_lstnew((void *)new_FC(eval_ident_FC(*str, data), line, i));
		if (!data->ident_FC)
			printf("Malloc failed, il faut gerer");
	}
	else if (data->ident_FC && eval_ident_FC(*str, data))
	{
		new = ft_lstnew((void *)new_FC(eval_ident_FC(*str, data), line, i));
		if (!new)
			printf("Malloc failed, il faut gerer");
		ft_lstadd_back(&data->ident_FC, new);
	}
	// else
	// {
	// 	check = data->NO + data->SE + data->WE + data->EA + data->F + data->C;
	// }
	//check_parsing_errors(data, 0);
	*str = NULL;
}

void	iter_line(t_cub3D *data, char **str, int i, char *line)
{
	while (line[++i] && !data->parsing_error)
	{
		//check_parsing_errors(data);
		if (line[i] == ' ' && line[i] != '\n' && line[i])
			delimitor(str, data, line, i);
		else if (line[i] != ' ' && line[i])
			get_char(line[i], str);
		// else if (line[i] == '\'' || line[i] == '\"')
		// {			
		// 	if ((i > 0 && !is_token(msh->prompt[i - 1]))
		// 		&& !is_space(msh->prompt[i - 1]))
		// 		delimitor(str, msh, 0);
		// 	i = is_quote(msh, i, &msh->prompt, 0);
		// }
	}
	//delimitor(&str, data, line, --i);
}

// Function to parse cmd from user input
int	get_list(t_cub3D *data, char *line)
{
	int		i;
	char	*str;	

	i = -1;
	str = NULL;
	iter_line(data, &str, i, line);
	//delimitor(&str, data);
	//check_parsing_errors(data);
	// check_tild(msh);
	// if (msh->parsing_error)
	// 	return (0);
	// ft_dup_list(msh);
	// expanded_cmd_list(msh, msh->cmd_expand);
	// ft_join_quote(msh);
	// pop_nulls(&msh->cmd_expand);
	return (!data->parsing_error);
}

// Function to handle space delimitor case
// will create and pus a new node with cmd and it's token

