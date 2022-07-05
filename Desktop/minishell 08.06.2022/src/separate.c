/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/05/09 19:49:58 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_find_length_quote(char *str, int i, int len, char c)
{
	while (str[i] != c)
	{
		i++;
		len++;
	}
	while (ft_char_resv(str, i) == 0 && str[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

static int	ft_find_length(char *str, int i)
{
	int	len;

	len = 0;
	if (ft_char_resv(str, i) == 2)
		return (2);
	else if (ft_char_resv(str, i) == 1)
		return (1);
	else
	{
		while (ft_char_resv(str, i) == 0 && str[i] != '\0' && str[i] != '"'
			&& str[i] != '\'')
		{
			i++;
			len++;
		}
		if (str[i] != '"' && str[i] != '\'')
			return (len);
		else if (str[i] == '"')
			len = ft_find_length_quote(str, i, len, '"');
		else
			len = ft_find_length_quote(str, i, len, '\'');
	}
	return (len);
}

char	**ft_assign_str(char *str, int num_elem, char **result)
{
	int	i;
	int	j;
	int	k;
	int	len;

	i = 0;
	j = 0;
	while (str[i] != '\0' && j < num_elem)
	{
		len = ft_find_length(str, i);
		result[j] = (char *)malloc(sizeof(char) * (len + 1));
		if (!result[j])
			return (NULL);
		k = 0;
		while (k < len && str[i] != '\0')
			result[j][k++] = str[i++];
		result[j][k] = '\0';
		j++;
	}
	result[j] = 0;
	return (result);
}

char	**ft_separate_str(char *str)
{
	char	**result;
	int		num_elem;

	num_elem = ft_get_num_elem(str);
	if (ft_char_resv(str, 0) == 0)
		num_elem++;
	result = malloc(sizeof(char *) * (num_elem + 1));
	if (!result)
		return (NULL);
	result = ft_assign_str(str, num_elem, result);
	return (result);
}
