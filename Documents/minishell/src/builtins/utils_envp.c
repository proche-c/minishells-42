/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/06/15 17:29:53 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	ft_is_in_envp(t_envp *envp, char *str) //VERIFICA SI LA LLAVE ESTA EN ENVP, 0 ES NO, 1 ES SI
{
	int	len;

	len = ft_strlen(str);
	while (envp != NULL)
	{
		if (ft_strncmp(str, ft_get_key(envp->key), len) == 0)
			return (1);
		envp = envp->next;
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