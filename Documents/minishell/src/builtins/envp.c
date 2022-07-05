/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/06/15 19:36:48 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_get_key(char *str) //OBTIENE LA LLAVE DE UNA STRING
{
	char	*key;
	int	len;
	int	y;
	
	len = 0;
	y = 0;
	while (str[len] != '\0' && str[len] != '=')
		len++;
	key = (char *)malloc(sizeof(char) * (len + 1));
	if (!key)
		return (NULL);
	while (y < len)
	{
		key[y] = str[y];
		y++;
	}
	return (key);
}

char	*ft_get_value(char *str) //OBTIENE EL VALOR DE UNA STRING
{
	char	*value;
	int	x;
	int	y;
	int	len;
	int	newlen;

	x = 0;
	y = 0;
	len = ft_strlen(str);
	while (str[x] != '\0' && str[x] != '=')
		x++;
	newlen = (len - x) - 1;
	value = (char *)malloc(sizeof(char) * (len - x));
	if (!value || newlen <= 0)
		return (NULL); //LEAKS DE MEMORIA, VERIFICAR Y MEJORAR SALIDA
	while (y < newlen)
	{
		value[y] = str[x + 1];
		x++;
		y++;
	}
	value[y] = '\0';
	return (value);
}

int	ft_len_envp(char **envp) //RETORNA LA LONGITUD DE ENVP
{
	int	x;

	x = 0;
	while (envp[x] != NULL)
		x++;
	return (x);
}

void	ft_order_envp(char **envp) //ORDENA ENVP
{
	char *temp;
	int	x;
	int	y;
	int	size;

	x = 0;
	y = 0;
	size = ft_len_envp(envp);
	while (x < size)
	{
		y = 0;
		while (y < (size - 1))
		{
			if (ft_strncmp(envp[y], envp[y + 1], ft_strlen(envp[y])) > 0)
			{
				temp = envp[y];
				envp[y] = envp[y + 1];
				envp[y + 1] = temp;
			}
			y++;
		}
		x++;
	}
}

char	**ft_create_new_envp_char(char **envp) // Crea un nuevo envp en char**
{
	char **newenvp;
	int	x;

	x = 0;
	newenvp = (char **)malloc(sizeof(char *) * (ft_len_envp(envp) + 1));
	if (!newenvp)
		return NULL;
	while (envp[x] != NULL)
	{
		newenvp[x] = ft_strdup(envp[x]);
		x++;
	}
	newenvp[x] = NULL;
	ft_order_envp(newenvp);
	return (newenvp);
}

static	int	ft_search_equal(char *str)
{
	int	x;

	x = 0;
	while (str[x] != '\0')
	{
		if (str[x] == '=')
			return (1);
		x++;
	}
	return (0);
}

static void	ft_type_envp(t_envp	*new_envp, char	*envp)
{
	// Verificar si hay igual, si hay puede ser dos tipos
	if (ft_search_equal(envp) == 1)
	{	
		if (ft_get_value(envp) != NULL)
			new_envp->type = 1; //Si hay valor es tipo 1 (pepe=test)
		else
			new_envp->type = 2; //Si tiene igual y no hay valor es tipo 2 (pepe=)
	}
	else // Si no hay igual es tipo 3 (pepe)
		new_envp->type = 3;

}

void	ft_create_envp(t_master *master, char **envp)
{
	char	**char_envp;
	t_envp	*new_envp;
	t_envp	*aux;
	int		x;
	
	x = 1;
	char_envp = ft_create_new_envp_char(envp); //**envp ya ordenada
	master->envp = ft_new_envp(ft_get_key(char_envp[0]), ft_get_value(char_envp[0]));
	new_envp = master->envp;
	while (char_envp[x] != NULL)
	{
		aux = ft_new_envp(ft_get_key(char_envp[x]), ft_get_value(char_envp[x]));
		ft_type_envp(aux, char_envp[x]); //FUNCION PARA SABER EL TIPO DE VARIABLE || 1 = (pepe) || 2 = (pepe=) || 3 = (pepe=valor)
		new_envp->next = aux;
		new_envp = new_envp->next;
		x++;
	}

	// new_envp = master->envp; // Visualizador de valores en envp
	// while(new_envp != NULL)
	// {
	// 	printf("KEY == (%s), VALUE == (%s)\n", new_envp->key, new_envp->value);
	// 	new_envp = new_envp->next;
	// }
	
		

	// free(char_envp); // Por alguna extraña razon, esto da error
}