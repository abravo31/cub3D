/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnieto-c <dnieto-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:39:55 by dnieto-c          #+#    #+#             */
/*   Updated: 2022/11/26 12:01:40 by dnieto-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp_lst;

	if (*lst)
	{
		while (*lst)
		{
			temp_lst = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = temp_lst;
		}
		*lst = 0;
	}
}

/*static void	ft_free_node(void *p)
{
	free(p);
}

static void	ft_lst_print(t_list *begin_list)
{
	t_list	*temp_lst;
	temp_lst = begin_list;
	
	while (temp_lst)
	{
		printf("%s\n", (char *)temp_lst->content);
		temp_lst = temp_lst->next;
	}
}

int	main(void)
{
    t_list  **list;
	t_list	*begin_list = ft_lstnew("Daniel");
    list = &begin_list;
	ft_lstadd_back(list, ft_lstnew("Alejandro"));
	ft_lstadd_front(list, ft_lstnew("Nieto"));
	ft_lstadd_back(list, ft_lstnew("Ecole"));
	ft_lstadd_front(list, ft_lstnew("42"));
	t_list	*element = ft_lstnew("Paris");
	t_list **address_element = &element;
	ft_lstadd_back(list, element);
	ft_lstadd_front(list, ft_lstnew("Barcelona"));
	ft_lstadd_back(list, ft_lstnew("Istambul"));
	ft_lstadd_front(list, ft_lstnew("Bogota"));
	ft_lst_print(begin_list);
	printf("Size of list : %d\n", ft_lstsize(begin_list));
	printf("address: %p\n", address_element);
	printf("\n\n\n");
	ft_lstclear(address_element, &ft_free_node);
	ft_lst_print(begin_list);
    printf("\n\n\n");
	printf("Size of list : %d\n", ft_lstsize(begin_list));
}*/