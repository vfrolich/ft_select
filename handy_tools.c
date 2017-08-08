/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handy_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:17:49 by vfrolich          #+#    #+#             */
/*   Updated: 2017/08/08 17:21:31 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

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
