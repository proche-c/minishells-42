/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 22:06:48 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_envp *envp, int fd)
{
	while (envp != NULL)
	{
		if (envp->type == 1)
			ft_put_str_3(envp->key, envp->value, TRUE, fd);
		else if (envp->type == 2)
			ft_put_str_2(envp->key, "=", TRUE, fd);
		envp = envp->next;
	}
}

static void	ft_type_envp(t_envp	*new_envp, char	*envp, char *value)
{
	if (ft_search_equal(envp) == 1)
	{
		if (value != NULL)
			new_envp->type = 1;
		else
			new_envp->type = 2;
	}
	else
		new_envp->type = 3;
}

void	ft_create_envp(t_master *master, char **envp)
{
	char	**char_envp;
	t_envp	*new_envp;
	t_envp	*aux;
	char	*value;
	int		x;

	x = 1;
	char_envp = ft_create_new_envp_char(envp);
	value = ft_get_value(char_envp[0]);
	master->envp = ft_new_envp(ft_get_key(char_envp[0]), value);
	new_envp = master->envp;
	master->env = char_envp;
	while (char_envp[x] != NULL)
	{
		value = ft_get_value(char_envp[x]);
		aux = ft_new_envp(ft_get_key(char_envp[x]), value);
		ft_type_envp(aux, char_envp[x], value);
		new_envp->next = aux;
		new_envp = new_envp->next;
		x++;
	}
	if (ft_is_in_envp(master->envp, "PATH") == FALSE)
		ft_export_with_var(master,
			"PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
}

void	ft_update_envp_aux(t_master *master)
{
	t_envp	*envp;
	char	**new_envp;
	char	*aux;
	int		x;

	x = 0;
	new_envp = malloc((ft_envpsize(master->envp) + 1) * sizeof(char *));
	envp = master->envp;
	while (x < ft_envpsize(master->envp))
	{
		aux = ft_strjoin(envp->key, "=");
		if (envp->value)
		{
			new_envp[x] = ft_strjoin(aux, envp->value);
			free(aux);
		}
		else
			new_envp[x] = aux;
		x++;
		envp = envp->next;
	}
	new_envp[x] = NULL;
	ft_clean_env_char(master);
	master->env = new_envp;
}

void	ft_update_envp(t_master *master)
{
	ft_update_envp_aux(master);
	ft_clean_env(master);
	ft_clean_env_char(master);
}
