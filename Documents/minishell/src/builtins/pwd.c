/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/06/09 11:04:31 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_pwd(void) //RETORNA LA DIRECCION ACTUAL
{
	char	*buf;

	buf = (char *)malloc(200 * sizeof(char));

	getcwd(buf, 200);

	//printf("%s\n", buf);
	return (buf);
}