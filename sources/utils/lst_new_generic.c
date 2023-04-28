#include "../../includes/cub3D_struct.h"

static t_list	*generic_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

static void	generic_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_node;
	// t_ident_coord	*coord;

	if (new)
	{
		if (*lst == NULL)
		{
			*lst = new;
			// coord = (t_ident_coord *) (*lst)->content;
			// printf("!!! %s\n", coord->path);
			// printf("%d\n", *lst == NULL);
		}
		else
		{
			last_node = generic_lstlast(*lst);
			last_node->next = new;
			// new->prev = last_node;
		}
	}
}

static t_list	*generic_lst_malloc_node(size_t data_size)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = malloc(data_size);
	if (!new_node->content)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

int	generic_lst_add_node(t_list **lst, void *data, size_t data_size)
{
	t_list			*new_node;
	// t_ident_coord	*coord;

	new_node = generic_lst_malloc_node(data_size);
	if (!new_node)
		return (1);
	new_node->content = ft_memcpy(new_node->content, data, data_size);
	// coord = (t_ident_coord *)new_node->content;
	// printf("??? %s\n", coord->path);
	generic_lstadd_back(lst, new_node);
	return (0);
}

// int	ft_add_item(t_lst **lst, char *meta)
// {
// 	char	*aux_metachar;
// 	size_t	size_meta;

// 	aux_metachar = ft_strdup(meta);
// 	if (!aux_metachar)
// 	{
// 		generic_lst_free(lst);
// 		return (1);
// 	}
// 	size_meta = sizeof(char) * ft_strlen_int(aux_metachar) + 1;
// 	if (generic_lst_add_node(lst, aux_metachar, size_meta))
// 	{
// 		free (aux_metachar);
// 		generic_lst_free(lst);
// 		return (1);
// 	}
// 	free (aux_metachar);
// 	return (0);
// }
