/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/05/09 19:49:58 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_check_str(char *str)
{
	int		len;
	char	*str_add;

	len = ft_strlen(str);
	while (str[len - 1] == '|' && str[len - 2] != '|')
	{
		str_add = readline(ANSI_COLOR_SHELL"🤖 Pipe ➤ "ANSI_COLOR_RESET);
		str = ft_strjoin(str, str_add);
		len = ft_strlen(str);
	}
	return (str);
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

char	*ft_check_quote(char *str)
{
	char	*str_add;
	int		quote;

	quote = ft_find_quote(str, '"');
	while (quote % 2 != 0)
	{
		str_add = readline(ANSI_COLOR_SHELL"🤖 dquote ➤ "ANSI_COLOR_RESET);
		str = ft_strjoin(str, str_add);
		quote = ft_find_quote(str, '"');
	}
	return (str);
}
