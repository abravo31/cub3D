#include "../../includes/cub3D_struct.h"


void print_coord_lst(t_list **begin_lst)
{
    t_list          *aux;
    t_ident_coord   *aux_coord;
    
    aux = *begin_lst;
	while (aux)
	{
        aux_coord = (t_ident_coord *)aux->content;
        printf("id %d\n", aux_coord->id);
	    printf("path %s\n", aux_coord->path);
        aux = aux->next;
    }
}


void print_FC_lst(t_list **begin_lst)
{
    t_list          *aux;
    t_ident_FC      *aux_FC;
    
    aux = *begin_lst;
	while (aux)
	{
        aux_FC = (t_ident_FC*)aux->content;
        printf("id %d\n", aux_FC->id);
        printf("R %d\n", aux_FC->R);
        printf("G %d\n", aux_FC->G);
        printf("B %d\n", aux_FC->B);
        aux = aux->next;
    }
}