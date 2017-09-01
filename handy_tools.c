/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handy_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:17:49 by vfrolich          #+#    #+#             */
/*   Updated: 2017/08/24 10:01:59 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"


char	*read_input(char *buffer)
{	
	ft_bzero(buffer, 4);
	read(0, buffer, 4);
	return (buffer);
}

char *strgen(size_t lenght)
{
	char *line;

	if (!(line = ft_strnew(lenght)))
	{
		ft_putendl_fd("ft_select: no memory	available for line buf, need: ", 2);
		ft_putendl_fd(" abort.", 2);
		exit(1);
	}
	return (line);
}

int wordcut(char *str, size_t width)
{
	char 	*tmp;
	size_t 	index;

	tmp = str;
	index = 0;
	while (index < width)
	{
		index++;
		tmp++;
	}
	return (*tmp ? 1 : 0);
}
