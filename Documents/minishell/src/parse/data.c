/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/06/15 13:12:38 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_find_len_cmds(char **cmds)//Esta funcion calcula el numero de argumentos de un elemento 
{
	int	len;

	// printf("FT_FIND_LEN_CMDS\n");
	len = 0;
	while (cmds[len])
		len++;
	return (len);
}

static t_data	*ft_get_args(t_data *data, char **cmds)//Esta funcion crea data->args, que son los argumentos del elemento en caso de que el elemento sea de tipo comando
{
	t_down	*temp;
	t_down	*aux;
	int	i;
	int	len;

	// printf("FT_GET_ARGS\n");
	len = ft_find_len_cmds(cmds) - 1;
	if (len >= 1) //evito crear down si solo hay un solo comando
	{
		data->down = ft_down_new(cmds[1]);
		if (!data->down) //Comprobacion de malloc
			return (NULL);
		temp = data->down;
		i = 2;
		while (i <= len)
		{
			aux = ft_down_new(cmds[i]);
			temp->next = aux;
			temp = temp->next;
			i++;
		}
	}
	return (data);
}

static t_data	*ft_get_cmds(t_master *master, t_data *new_data, int k)//Esta funcion crea data->cmd, que es el nombre del comando en el caso de que el elemento sea de tipo comando
{
	int		len;
	char	**cmds;

	// printf("FT_GET_CMDS\n");
	len = 0;
	cmds = ft_split(master->elem[k], ' ');
	if (!cmds) //Comprobacion de malloc
		return (NULL);
	while (cmds[len])
		len++;
	new_data->num_args = len - 1;
	new_data->cmd = ft_strdup(cmds[0]);
	if (!new_data->cmd)
	{
		free(cmds);
		return (NULL);
	}
	new_data = ft_get_args(new_data, cmds);
	free(cmds);
	return (new_data);
}

t_data	*ft_get_data(t_master *master, t_data *new_data, int j) //Esta funcion asigna el data->type a cada elemento de la lista
{
	int	i;

	// printf("FT_GET_DATA REAL\n");
	i = 0;
	while (master->elem[j][i] == ' ')
		i++;
	if (master->elem[j][i] == '|')
		new_data->type = PIPE;
	else if (master->elem[j][i] == '>')
	{
		if (master->elem[j][i + 1] && master->elem[j][i + 1] == '>')
			new_data->type = DFILE_OUT;
		else
			new_data->type = FILE_OUT;
	}
	else if (master->elem[j][i] == '<')
	{
		if (master->elem[j][i + 1] && master->elem[j][i + 1] == '<')
			new_data->type = DFILE_IN;
		else
			new_data->type = FILE_IN;
	}
	else
		new_data = ft_get_cmds(master, new_data, j);
	if (!new_data) //Verificar caso
		master->error = 1;
	return (new_data);
}

/*
Verificar los errores e agregar la informacion en master->error

*/