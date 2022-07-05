/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/05/09 19:49:58 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_entry	*ft_find_last(t_entry *lst)//Esta funcion va al ultimo elemento de la lista para seaber donde anadir el siguiente elemento
{
	t_entry	*temp;

	temp = lst;
	if (lst)
	{
		while (temp->next)
			temp = temp->next;
		return (temp);
	}
	return (NULL);
}

/* added */

static int	ft_find_len_cmds(char **cmds)
{
	int	len;


	len = 0;
	while (cmds[len])
		len++;
	return (len);
}

static t_data	*ft_get_args(t_data *data, char **elem, char **cmds)
{
	int	i;
	int	j;
	int	len;

	printf("FT_GET_ARGS2222222\n");

	len = ft_find_len_cmds(cmds) - 1;
	data->args = malloc(sizeof(char *) * (len + 1));
	printf("len of cmds is %d\n",len);
	i = 1;
	j = 0;
	while (j < len)
	{
		data->args[j] = ft_strdup(cmds[i]);
		printf("data: args %d is %s\n", j, data->args[j]);
		if (!data->args[j])
		{
			ft_error_5(elem, data, cmds);
			return (NULL);
		}
		else
		{
			// free(cmds[i]);
			i++;
			j++;
		}
	}
	data->args[j] = 0;
	return (data);
}

static t_data	*ft_get_cmds(t_data *data, char **elem, int k)
{
	int		len;
	char	**cmds;
	int j;

	printf("FT_GET_CMDS22222\n");
	// printf("\nELEMENTO GET CMDS 1 = (%s)\n\n", data->args[0]);
	len = 0;
	cmds = ft_split(elem[k], ' ');
	while (cmds[len])
		len++;
	data->cmd = ft_strdup(cmds[0]);
	if (!data->cmd)
		ft_error_3(elem, data, cmds);
	else
	{
		data->args = malloc(sizeof(char *) * (len));
		if (!data->args)
		{
			ft_error_4(elem, data, cmds);
			return (NULL);
		}
		else
			data = ft_get_args(data, elem, cmds);
		j = 0;
		while (data->args[j])
		{
			printf("22222after cmds: args %d is %s\n", j, data->args[j]);
			j++;
		}
		free(cmds);

		printf("\n22222ELEMENTO GET CMDS 2 = (%s)\n\n", data->args[0]);
		return (data);
	}
	printf("\n22222ELEMENTO GET CMDS 2.1 = (%s)\n\n", data->args[0]);
	return (NULL);
}

t_data	*ft_get_data2(t_data *data, char **elem, int j, t_entry *first)
{
	int	i;
	// int k;

	(void)first;
	printf("FT_GET_DATA\n");
	// if (first->data->cmd)
	printf("FT_GET_DATA FIRST 1== (%s)\n", first->data->args[0]);
	i = 0;
	while (elem[j][i] == ' ')
		i++;
	printf("DONDE ESTOY 1\n");
	printf("FT_GET_DATA FIRST 2 == (%s)\n", first->data->args[0]);
	if (elem[j][i] == '|')
	{
		printf("DONDE ESTOY 2\n");
		printf("FT_GET_DATA FIRST 3 == (%s)\n", first->data->args[0]);
		data->type = PIPE;
		return (data); //agregado opor victor
	}
	else if (elem[j][i] == '>')
	{
		printf("DONDE ESTOY 3\n");
		printf("FT_GET_DATA FIRST 4 == (%s)\n", first->data->args[0]);
		if (elem[j][i + 1] && elem[j][i + 1] == '>')
			data->type = DFILE_OUT;
		else
			data->type = FILE_OUT;
	}
	else if (elem[j][i] == '<')
	{
		printf("DONDE ESTOY 4\n");
		printf("FT_GET_DATA FIRST 5 == (%s)\n", first->data->args[0]);
		if (elem[j][i + 1] && elem[j][i + 1] == '<')
			data->type = DFILE_IN;
		else
			data->type = FILE_IN;
	}
	else
	{
		printf("FT_GET_DATA FIRST PRE ELSEEE 6 == (%s)\n", first->data->args[0]);
		data = ft_get_cmds(data, elem, j);
		printf("FT_GET_DATA FIRST POST ELSEEE 6 == (%s)\n", first->data->args[0]);
	}
	printf("FT_GET_DATA FIRST 6 == (%s)\n", first->data->args[0]);
	printf("DONDE ESTOY 5\n");
	printf("\nFET_GET_DATA TEST 2== (%s)\n\n", data->args[0]);
		// 	k = 0;
		// while (data->args[k])
		// {
		// 	printf("after get all data: args %d is %s\n", k, data->args[k]);
		// 	k++;
		// }

	return (data);
}

/* end */
void	ft_get_new_entry(t_entry *first, char **elem, int i)//Esta funcion crea un nuevo elemento de la lista, una nueva estructura data y la une al final de la lista existente
{
	t_entry	*new_entry;
	t_entry	*last;
	t_data	*new_data;

	(void)i;
	(void)elem;
	printf("FT_GET_NEW_ENTRY\n");
	new_entry = malloc(sizeof(t_entry *));
	last = malloc(sizeof(t_entry *));
	printf("\nELEMENTO TEST 1== (%s)\n\n", first->data->args[0]);
	if (new_entry && last)
	{
		last = ft_find_last(first);
		new_data = malloc(sizeof(t_data *));
		if (new_data && new_entry)
		{
			printf("\nELEMENTO TEST 2== (%p)\n\n", first->data->args[0]);
			new_data = ft_initialize_data(new_data);
			printf("\nELEMENTO TEST 3== (%p)\n\n", first->data->args[0]);
			new_data = ft_get_data2(new_data, elem, i, first); // ERROR
			printf("\nELEMENTO TEST 4== (%p)\n\n", first->data->args[0]);
			last->next = new_entry;
			printf("\nELEMENTO TEST 5== (%p)\n\n", first->data->args[0]);
			new_entry->data = new_data;
			printf("\nELEMENTO TEST 6== (%s)\n\n", first->data->args[0]);
			new_entry->next = NULL;
		}
		else
			return ;
	}
	printf("\nELEMENTO TEST 7== (%s)\n\n", first->data->args[0]);
}

t_entry	*ft_get_all_entry(char **elem, t_entry *first)//Esta funcion es un bucle para asignar el resto de elementos de la lista
{
	int	i;
	int	num_elem;

	printf("FT_GET_ALL_ENTRY\n");
	num_elem = ft_get_elem(elem);
	i = 1;
	while (i < num_elem)
	{
		printf("hola elemento %d\n", i);
		ft_get_new_entry(first, elem, i);
		i++;
	}
	return (first);
}

t_entry	*ft_get_first_elem(char **elem, t_entry *first)//Esta funcoin crea la estructura de datos del primer elemento de la lista y se lo asigna a first
{
	t_data	*data;

	printf("FT_GET_FIRST_ELEMENT\n");
	data = malloc(sizeof(t_data *));
	if (!data)
		ft_error_2(elem);
	else
	{
		data = ft_initialize_data(data);
		data = ft_get_data(data, elem, 0);
		if (data)
		{
			first->data = data;
			first->next = NULL;
			return (first);
		}
	}
	return (NULL);
}

t_entry	*ft_get_entry(char *str, t_entry *first)//Esta funcion construye la lista enlazada y luego devuelve el puntero que apunta al primer elemento de la lista a ft_parse and exec
{
	char	**elem;
	//int i;
	int k;
	printf("FT_GET_ENTRY\n");
	elem = ft_separate_str(str);
	// elem es un doble puntero que contiene cada elemento de la entrada separado por un separador(los separadores son |,<<,<,>>,>)
	/*printf("voy a imprimir elem\n");
	i = 0;
	while(elem[i])
	{
		printf("elem %d is %s\n", i, elem[i]);
		i++;
	}*/
	first = ft_get_first_elem(elem, first);
	printf("\n\nPRIMER ELEMENTO == (%s)\n\n", first->data->args[0]);
	if (first)
		ft_get_all_entry(elem, first);
	else
	{
		free(first);
		return (NULL);
	}
	printf("\n\nPRIMER POST AGREGAR ELEMENTO == (%s)\n\n", first->data->args[0]);
				k = 0;
		while (first->data->args[k])
		{
			printf("GET ENTRY after get all data: args %d is %s\n", k, first->data->args[k]);
			k++;
		}

	return (first);
}
