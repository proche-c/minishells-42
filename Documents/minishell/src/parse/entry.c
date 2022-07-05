/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/06/15 13:22:41 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_get_value_list(t_master *master)//Esta funcion crea la estructura de datos del primer elemento de la lista y se lo asigna a first
{
	t_data	*newlist;
	t_data	*temp;
	int		x;

	x = 1;
	// printf("FT_GET_FIRST_ELEMENT\n");
	master->list = ft_new_cmd(); //Malloc creado e inicializado a 0/NULL
	if (!master->list)
	{
		master->error = 1;
		return ;
	}
	master->list = ft_get_data(master, master->list, 0); //Le doy valor al primer elemento
	

	temp = master->list;
	while (x < master->num_elem)
	{
		newlist = ft_new_cmd();
		// newlist->data = ft_get_data(newlist->data, master->elem, x);
		newlist = ft_get_data(master, newlist, x);
		temp->next = newlist;
		temp = temp->next;
		x++;
	}
	
	// /* IMPRIMIR LISTA COMPLETA */
	printf("MASTER STR == (%s), ELEMENTOS == (%i)\n\n", master->str, master->num_elem);
	// int	x = 0; // LEER LISTA
	t_down *aux;
	temp = master->list;
	while (temp != NULL)
	{
		x = 0;
		aux = temp->down;
		if (temp->type == 1)
			printf("PIPE\n");
		else
		{
			printf("COMANDO == (%s), #ARGUMENTOS = (%i) ARGUMENTOS == ", temp->cmd, temp->num_args);
			while (aux != NULL)
			{
					printf("(%s) ", aux->arg);
				aux = aux->next;
				x++;
			}
			printf("\n");
		}
		temp = temp->next;
	}
	// /* FIN */
}

void	ft_get_entry(t_master *master)//Esta funcion construye la lista enlazada y luego devuelve el puntero que apunta al primer elemento de la lista a ft_parse and exec
{
	// printf("FT_GET_ENTRY, str == (%s)\n\n", master->str);
	ft_separate_str(master); // Split raro
	ft_get_value_list(master); // Obtengo el valor de todos
}
