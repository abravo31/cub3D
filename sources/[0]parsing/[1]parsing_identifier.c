#include "../../includes/cub3D_struct.h"

// Function that returns 1 or 0 weither c is a token or not
// int	is_token(char c)
// {
// 	size_t				i;
// 	static const char	*tokens[] = {
// 		">",
// 		"<",
// 		"|",
// 		NULL,
// 	};

// 	i = 0;
// 	while (tokens[i])
// 	{
// 		if (tokens[i][0] == c)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

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

// Function to return corresponding token from string
t_ident_type	eval_ident_type(char *ident)
{
	if (is_identical("NO", ident))
		return (NO);
	else if (is_identical("SE", ident))
		return (SE);
	else if (is_identical("WE", ident))
		return (WE);
	else if (is_identical("EA", ident))
		return (EA);
	else if (is_identical("F", ident))
		return (F);
	else if (is_identical("C", ident))
		return (C);
	return (UNASSIGNED);
}

void	cmd_without_quotes(t_minishell *msh, char prompt, char **str)
{
	if ((is_token(prompt) && *str && !is_token(*str[0]))
		|| (!is_token(prompt) && *str && is_token(*str[0])))
		delimitor(str, msh, 0);
	if ((prompt == '>' || prompt == '<')
		&& *str && *str[0] == '|')
		delimitor(str, msh, 0);
}

void	iter_line(t_cub3D *cub3D, char **str, int i, char *line)
{
	while (line[++i] && !cub3D->parsing_error)
	{
		check_parsing_errors(cub3D, 0);
		// if ([i] == '$' 
		// 	&& (msh->prompt[i + 1] == '"' || msh->prompt[i + 1] == '\''))
		// 	msh->prompt[i] = ' ';
		if (line[i] == ' ')
			delimitor(str, cub3D, 1);
		else if (!is_space(line[i]) && (line[i] != '\'' 
		&& msh->prompt[i] != '\"'))
		{
			cmd_without_quotes(msh, msh->prompt[i], str);
			get_char(msh->prompt[i], str);
		}
		else if (msh->prompt[i] == '\'' || msh->prompt[i] == '\"')
		{			
			if ((i > 0 && !is_token(msh->prompt[i - 1]))
				&& !is_space(msh->prompt[i - 1]))
				delimitor(str, msh, 0);
			i = is_quote(msh, i, &msh->prompt, 0);
		}
	}
}

// Function to parse cmd from user input
int	get_list(t_cub3D *cub3D, char *line)
{
	int		i;
	char	*str;	

	i = -1;
	str = NULL;
	iter_line(cub3D, &str, i, line);
	delimitor(&str, cub3D, 0);
	check_parsing_errors(msh, 1);
	check_tild(msh);
	if (msh->parsing_error)
		return (0);
	ft_dup_list(msh);
	expanded_cmd_list(msh, msh->cmd_expand);
	ft_join_quote(msh);
	pop_nulls(&msh->cmd_expand);
	return (!msh->parsing_error);
}

// Function to handle space delimitor case
// will create and pus a new node with cmd and it's token
void	delimitor(char **str, t_cub3D *cub3D, int space)
{
	t_list	*new;

	if (!*str || cub3D->parsing_error)
		return ;
	if (cub3D->ident_coord == NULL && eval_ident_type(*str) <= 3 && eval_ident_type(*str))
	{
		cub3D->ident_coord = ft_lstnew((void *)new_cmd(*str, eval_ident_type(*str), space));
		if (!cub3D->ident_coord)
			printf("Malloc failed, il faut gerer");
		//add_to_garbage_collector((void *)&msh->cmd, CMD);
	}
	else if (cub3D->ident_FC == NULL && eval_ident_type(*str) <= 3 && eval_ident_type(*str))
	{
		/* code */
	}
	
	else
	{
		new = ft_lstnew((void *)new_cmd(*cmd, eval_token(*cmd), space));
		if (!new)
		{
			free_garbage_collector(ALL);
			printf("error while adding a delimitor,
			still not error or way toe xit this function!\n");
			return ;
		}
		ft_lstadd_back(&msh->cmd, new);
	}
	check_parsing_errors(msh, 0);
	*cmd = NULL;
}
