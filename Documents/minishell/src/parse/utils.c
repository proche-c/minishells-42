/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/06/09 11:10:19 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_eval_dir(int len, char *str, int i, char c)
{
	int	result;

	if ((i + 1) < len && str[i + 1] == c)
		result = 2;
	else
		result = 1;
	return (result);
}

int	ft_get_e(int quote, int d_quote, char *str)
{
	int	num_elem;
	int	i;

	i = 0;
	num_elem = 0;
	while (str[i] != '\0')
	{
		if (ft_char_resv(str, i) == 1 && quote % 2 == 0 && d_quote % 2 == 0)
			num_elem++;
		else if (ft_char_resv(str, i) == 2 && quote % 2 == 0
			&& d_quote % 2 == 0)
		{
			num_elem++;
			i++;
		}
		else if (str[i] == '\'' && d_quote % 2 == 0)
			quote++;
		else if (str[i] == '"' && quote % 2 == 0)
			d_quote++;
		i++;
	}
	return (num_elem);
}

int	ft_get_num_elem(char *str)
{
	int	num_elem;
	int	quote;
	int	d_quote;

	quote = 0;
	d_quote = 0;
	num_elem = ft_get_e(quote, d_quote, str);
	num_elem = 2 * num_elem;
	return (num_elem);
}

int	ft_char_resv(char *str, int i)
{
	int	result;
	int	len;

	result = 0;
	len = ft_strlen(str);
	if (str[i] == '<')
		result = ft_eval_dir(len, str, i, '<');
	else if (str[i] == '>')
		result = ft_eval_dir(len, str, i, '>');
	else if (str[i] == '|')
		result = 1;
	return (result);
}

