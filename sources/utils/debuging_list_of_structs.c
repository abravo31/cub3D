#include "../../includes/cub3D_struct.h"

void print_coord_lst(t_list **begin_lst)
{
	t_list          *aux;
	t_coord   *aux_coord;
	
	aux = *begin_lst;
	while (aux)
	{
		aux_coord = (t_coord *)aux->content;
		printf("id %d\n", aux_coord->id);
		printf("path %s\n", aux_coord->path);
		aux = aux->next;
	}
}


void print_FC_lst(t_list **begin_lst)
{
	t_list          *aux;
	t_fc      *aux_fc;
	
	aux = *begin_lst;
	while (aux)
	{
		aux_fc = (t_fc*)aux->content;
		printf("id %d\n", aux_fc->id);
		printf("R %d\n", aux_fc->r);
		printf("G %d\n", aux_fc->g);
		printf("B %d\n", aux_fc->b);
		aux = aux->next;
	}
}