/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/05/09 19:49:58 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data	*ft_initialize_data(t_data *data) //Inicialida la estructura data
{
	printf("FT_INITIALIZE_DATA\n");
	data->type = 0;
	data->cmd = NULL;
	data->args = NULL;
	return (data);
}

static int	ft_find_len_cmds(char **cmds)//Esta funcion calcula el numero de argumentos de un elemento 
{
	int	len;

	printf("FT_FIND_LEN_CMDS\n");
	len = 0;
	while (cmds[len])
		len++;
	return (len);
}

static t_data	*ft_get_args(t_data *data, char **elem, char **cmds)//Esta funcion crea data->args, que son los argumentos del elemento en caso de que el elemento sea de tipo comando
{
	int	i;
	int	j;
	int	len;

	printf("FT_GET_ARGS\n");

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

static t_data	*ft_get_cmds(t_data *data, char **elem, int k)//Esta funcion crea data->cmd, que es el nombre del comando en el caso de que el elemento sea de tipo comando
{
	int		len;
	char	**cmds;
	int j;

	printf("FT_GET_CMDS\n");
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
			printf("after cmds: args %d is %s\n", j, data->args[j]);
			j++;
		}
		free(cmds);

		printf("\nELEMENTO GET CMDS 2 = (%s)\n\n", data->args[0]);
		return (data);
	}
	printf("\nELEMENTO GET CMDS 2.1 = (%s)\n\n", data->args[0]);
	return (NULL);
}

t_data	*ft_get_data(t_data *data, char **elem, int j)//Esta funcion asigna el data->type a cada elemento de la lista
{
	int	i;
	// int k;

	// (void)first;
	printf("FT_GET_DATA\n");
	// if (first->data->cmd)
	// printf("FT_GET_DATA FIRST 1 CMD== (%p)\n", first->data->cmd);
	i = 0;
	while (elem[j][i] == ' ')
		i++;
	printf("DONDE ESTOY 1\n");
	if (elem[j][i] == '|')
	{
		printf("DONDE ESTOY 2\n");
		data->type = PIPE;
		return (data); //agregado opor victor
	}
	else if (elem[j][i] == '>')
	{
		printf("DONDE ESTOY 3\n");
		if (elem[j][i + 1] && elem[j][i + 1] == '>')
			data->type = DFILE_OUT;
		else
			data->type = FILE_OUT;
	}
	else if (elem[j][i] == '<')
	{
		printf("DONDE ESTOY 4\n");
		if (elem[j][i + 1] && elem[j][i + 1] == '<')
			data->type = DFILE_IN;
		else
			data->type = FILE_IN;
	}
	else
		data = ft_get_cmds(data, elem, j);
	// printf("FT_GET_DATA FIRST 2 == (%s)\n", first->data->args[0]);
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
