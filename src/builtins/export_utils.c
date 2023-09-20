/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/07/16 16:39:44 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_temp_type(t_envp *temp, char *aux, int fd)
{
	if (temp->type == 1)
	{
		aux = ft_strjoin(temp->key, "=\"");
		aux = ft_strjoin(aux, temp->value);
		aux = ft_strjoin(aux, "\"\n");
		ft_putstr_fd(aux, fd);
	}
	else if (temp->type == 2)
	{
		aux = ft_strjoin(temp->key, "=\"\"\n");
		ft_putstr_fd(aux, fd);
	}
	else if (temp->type == 3)
	{
		aux = ft_strjoin(temp->key, "\n");
		ft_putstr_fd(aux, fd);
	}
}

int	ft_check_first_value(char *key, char *arg)
{
	char	*aux;

	print("FT_CHECK_FIRST_VALUE (%i)", ft_has_char(key, ':'));
	if ((key[0] >= '0' && key[0] <= '9')
		|| ft_has_char(key, '/') > 0
		|| ft_has_char(key, ' ') > 0
		|| ft_has_char(key, '%') > 0
		|| ft_has_char(key, ':') > 0)
	{
		aux = ft_strjoin("export: `", arg);
		aux = ft_strjoin(aux, "': not a valid identifier\n");
		ft_putstr_fd(aux, 2);
		g_returnvalue = 1;
		return (1);
	}
	else
		return (0);
}

char	*ft_get_value_export(t_master *master, char *key)
{
	t_envp	*temp;

	temp = master->envp;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key) + 1) == 0)
		{
			return (temp->value);
		}
		temp = temp->next;
	}
	return (NULL);
}

int	ft_has_equal(char *str)
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
