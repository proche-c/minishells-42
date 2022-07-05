/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/06/09 11:10:15 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_check_str(t_master *master)
{
	int		len;
	char	*str_add;

	len = ft_strlen(master->str);
	while (master->str[len - 1] == '|' && master->str[len - 2] != '|')
	{
		str_add = readline(ANSI_COLOR_SHELL"🤖 Pipe ➤ "ANSI_COLOR_RESET);
		master->str = ft_strjoin(master->str, str_add);
		len = ft_strlen(master->str);
	}
}

int	ft_find_quote(char *str, char c)
{
	int	i;
	int	quote;

	quote = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			quote++;
		i++;
	}
	return (quote);
}

void	ft_check_quote(t_master *master)
{
	char	*str_add;
	int		quote;

	quote = ft_find_quote(master->str, '"');
	while (quote % 2 != 0)
	{
		str_add = readline(ANSI_COLOR_SHELL"🤖 dquote ➤ "ANSI_COLOR_RESET);
		master->str = ft_strjoin(master->str, str_add);
		quote = ft_find_quote(master->str, '"');
	}
}
