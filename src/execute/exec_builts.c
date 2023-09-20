/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 22:10:34 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_builtins(t_master *master, t_data	*list, int fd)
{
	if (ft_strncmp(list->cmd, "cd", 3) == 0)
		ft_is_cd(master, list);
	else if (ft_compare_upper_lower(list->cmd, "echo") == 1)
		ft_echo(list, fd);
	else if (ft_strncmp(list->cmd, "export", 7) == 0)
		ft_is_export(master, list, fd);
	else if (ft_compare_upper_lower(list->cmd, "env") == 1)
		ft_is_env(master, list, fd);
	else if (ft_strncmp(list->cmd, "unset", 6) == 0)
		ft_is_unset(master, list);
	else if (ft_compare_upper_lower(list->cmd, "pwd") == 1)
		ft_pwd(master);
	else if (ft_strncmp(list->cmd, "exit", 5) == 0)
		ft_exit(master, list);
	if (master->num_pipes > 0)
		exit(0);
}
