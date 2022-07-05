/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/05/31 13:41:09 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
			// printf("(%s), (%s), (%i)# == (%i)\n", envp[y], envp[y + 1], ft_strlen(envp[y]), ft_strncmp(envp[y], envp[y + 1], ft_strlen(envp[y])));
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

int	ft_len_envp(char **envp) //RETORNA LA LONGITUD DE ENVP
{
	int	x;

	x = 0;
	while (envp[x] != NULL)
		x++;
	return (x);
}

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

int	ft_has_quote(char *str) //VERIFICA SI TIENE COMILLAS, 0 ES NO, 1 ES SI
{
	int	x;

	x = 0;
	while (str[x] != '\0')
	{
		if (str[x] == '\"')
			return (1);
		x++;
	}
	return (0);
}

int	ft_is_in_envp(char **envp, char *str) //VERIFICA SI LA LLAVE ESTA EN ENVP, 0 ES NO, 1 ES SI
{
	int	len;
	int x;

	x = 0;
	len = ft_strlen(str);
	while (envp[x] != NULL)
	{
		if (ft_strncmp(str, ft_get_key(envp[x]), len) == 0)
			return (1);
		x++;
	}
	return (0);
}

char	*ft_get_value_without_quotes(char *str) //OBTIENE EL VALOR CUANDO VALUE NO TIENE COMILLAS
{
	char	*value;
	int	x;
	int	y;
	int	z;
	int	len;
	int	newlen;

	x = 0;
	y = 0;
	z = 0;
	len = ft_strlen(str);
	// printf("FT_GET_VALUE\n");
	while (str[x] != '\0' && str[x] != '=')
		x++;
	z = x + 1;
	while (str[z] != '\0' && str[z] != ' ')
		z++;
	// printf("VERDADERO LEN == (%i), %i\n\n\n", len - z, (z - x - 1));
	newlen = (z - x - 1);
	if (newlen <= 0)
		return (NULL);
	else
		newlen += 2;
	value = (char *)malloc(sizeof(char) * (newlen + 1));
	if (!value)
		return (NULL);
	//newlen = (len - z) - 1;
	if (newlen <= 0)
		return (NULL);
	// printf("SIZE OF VALUE == (%i)\n", newlen);
	while (y < newlen)
	{
		if (y == 0 || y == newlen - 1)
		{
			value[y] = '\"';
			y++;
		}
		else
		{
			value[y] = str[x + 1];
			x++;
			y++;
		}
	}
	value[y] = '\0';
	// printf("ft_get_value_without_quotes == VALUE == (%s)\n", value);
	return (value);
	
}