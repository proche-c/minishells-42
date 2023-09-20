/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 23:33:16 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_data	*ft_num_cmds_aux(t_data *list)
{
	list = list->next;
	while (list->type == 0)
	{
		list = list->next;
		if (!list)
			break ;
	}
	return (list);
}

void	ft_num_cmds(t_master *master)
{
	t_data	*list;
	int		x;

	x = 0;
	list = master->list;
	while (list)
	{
		if ((x == 0 && list->type == 2) || (x == 0 && list->type == 3)
			|| (x == 0 && list->type == 4) || list->type == 0
			|| list->type == 6)
			x++;
		if (list->type > 1 && list->type < 6)
		{
			list = ft_num_cmds_aux(list);
			if (!list)
				break ;
		}
		if (list->type == PIPE)
		{
			if (list->next && list->next->type == 2)
				x++;
		}
		list = list->next;
	}
	master->num_cmds = x;
}

void	ft_get_paths_vesionvictor(t_master *master, t_data *list)
{
	char	**bin_paths;
	t_envp	*result;
	char	*cmd;
	int		i;

	result = ft_find_path(master);
	bin_paths = ft_split(result->value, ':');
	cmd = ft_strjoin("/", list->cmd);
	i = 0;
	while (bin_paths[i])
	{
		bin_paths[i] = ft_strjoin(bin_paths[i], cmd);
		i++;
	}
	master->bin_paths = bin_paths;
}

void	ft_prev_execute_builtins(t_master *master, t_data *list)
{
	if (master->fd_redir != 0)
	{
		if (master->redir_type == 2 || master->redir_type == 4)
			ft_exec_builtins(master, list, master->fd_redir);
	}
	else if (master->num_pipes != 0)
	{
		ft_exec_builtins(master, list,
			master->pipes[master->executed_pipes + 1][WRITE]);
	}
	else
		ft_exec_builtins(master, list, 1);
}

void	ft_prev_execute_cmds(t_master *master, t_data *list)
{
	int	status_waitpid;
	int	pid;

	status_waitpid = 666;
	pid = 0;
	if (master->executed_cmds == 0)
	{
		if (master->num_cmds == 1 && list->type == BUILTIN)
		{
			if (master->num_pipes > 0)
				ft_cmd_1(master, list);
			else if (master->fd_redir != 0)
			{
				if (master->redir_type == 2 || master->redir_type == 4)
					ft_exec_builtins(master, list, master->fd_redir);
				else if (master->redir_type == 3)
					ft_exec_builtins(master, list, 1);
			}
			else
				ft_exec_builtins(master, list, 1);
			return ;
		}
		pid = fork();
		if (pid == 0)
			ft_cmd_1(master, list);
		else
		{
			if (master->num_pipes != 0)
				close(master->pipes[0][WRITE]);
		}
	}
	else if (master->executed_cmds == (master->num_cmds - 1))
	{
		pid = fork();
		if (pid == 0)
			ft_cmd_3(master, list);
		else
			close(master->pipes[0][READ]);
	}
	else
	{
		pid = fork();
		if (pid == 0)
			ft_cmd_2(master, list);
		else
		{
			close(master->pipes[master->executed_pipes][READ]);
			close(master->pipes[master->executed_pipes + 1][WRITE]);
		}
	}
	if (master->fd_redir != 0)
	{
		close(master->fd_redir);
		master->fd_redir = 0;
	}
	waitpid(pid, &status_waitpid, 0);
	g_returnvalue = WEXITSTATUS(status_waitpid);
	if (g_returnvalue == 127)
	{
		ft_return_error(list->cmd, ": command not found\n");
		g_returnvalue = 127;	
	}
	else if (g_returnvalue == 126)
		printf("%s: Permission denied\n", list->cmd);
	else if (g_returnvalue == 130)
	{
		ft_return_error(list->cmd, ": No such file or directory\n");
		g_returnvalue = 127;
	}
	if (WIFSIGNALED(status_waitpid))
	{
		if (WTERMSIG(status_waitpid) == 2)
			g_returnvalue = 130;
	}
}

int	ft_is_absolute_path(char *str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (str[x] == '/')
			return (1);
		x++;
	}
	return (0);
}

void	ft_execute_cmd_real(t_master *master, t_data *list)
{
	char	*str;
	int		y;

	y = 0;
	if (ft_strlen(list->cmd) == 0)
	{
		ft_return_error(list->cmd, ": command not found\n");
		exit(127);
	}
	else if (ft_strncmp(list->cmd, "test", 5) == 0)
	{
		exit(1);
	}
	else if (list->cmd[0] == '/' && access(list->cmd, F_OK) != 0)
	{
		exit(130);
	}
	else if (ft_is_directory(list->cmd) == TRUE)
	{
		exit(130);
	}
	if (ft_is_absolute_path(list->cmd) == 1)
	{
		if (execve(list->cmd, list->args, master->env) == -1)
			exit(126);
	}
	else if (list->cmd[0] == '/')
	{
		exit(130);
	}
	if (ft_is_in_envp(master->envp, "PATH") == 0)
		exit(127);
	if (list->cmd[0] == '.' && list->cmd[1] == '/')
	{
		str = &list->cmd[2];
		str = ft_strjoin(ft_my_path(), "/");
		str = ft_strjoin(str, &list->cmd[2]);
		if (execve(str, list->args, master->env) == -1)
			exit(126);
	}
	else if (ft_is_absolute_path(list->cmd) == 1)
		execve(list->cmd, list->args, master->env);
	else
	{
		ft_get_paths_vesionvictor(master, list);
		while (master->bin_paths[y])
		{
			if (access(master->bin_paths[y], F_OK) == 0)
			{
				if (execve(master->bin_paths[y], list->args, master->env) == -1)
					exit(126);
			}
			y++;
		}
	}
	exit(127);
}

void	ft_to_execute(t_master *master, t_data *list)
{
	if (list->type == BUILTIN)
		ft_prev_execute_builtins(master, list);
	else
		ft_prev_execute_cmds(master, list);
}

int ft_is_directory(char *path)
{
	struct stat stats;

	stat(path, &stats);
	if (S_ISDIR(stats.st_mode))
		return (1);
	return (0);
}