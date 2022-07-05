/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/06/09 11:04:34 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_unset(char **envp, char *str)
{
	char	**newenvp;
	int	size;
	int	x;
	int	y;
	int	z;

	x = 0;
	y = 0;
	z = 0;
	size = ft_len_envp(envp);
	// printf("LEN INICIAL UNSET == (%i), STR == (%s)\n", size, str);
	while (envp[x] != NULL)
	{
		if (ft_strncmp(str, ft_get_key(envp[x]), ft_strlen(str) + 1) == 0) //Comparo el unset que estoy buscando con cada variable de entorno
		{
			// printf("(%s) SI SE ENCUENTRA EN ENVP\n", str);
			newenvp = (char **)malloc(sizeof(char *) * size);
			if (!newenvp)
				return (NULL);
			while (envp[z] != NULL)
			{
				if (ft_strncmp(str, ft_get_key(envp[z]), ft_strlen(str) + 1) == 0)
				{
					// printf("NO SE AGREGARA == (%s)\n", envp[z]);
					z++;;
				}	
				else
				{
					newenvp[y] = ft_strdup(envp[z]);
					y++;
					z++;
					//printf("AGREGANDO VALOR\n");
				}
				
			}
			// printf("EXIT BUCLE\n");
			newenvp[y] = NULL;
			
			// printf("Y YA SE ELIMINO, LEN NEW == (%i)\n", ft_len_envp(newenvp));
			free(envp);
			return (newenvp);
			//ft_export(newenvp);
		}
		x++;
	}
	return (envp);
}