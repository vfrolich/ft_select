/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capability.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 11:03:40 by vfrolich          #+#    #+#             */
/*   Updated: 2017/08/24 09:57:54 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

char	*get_capstring(char *cap)
{
	char *capability;

	if (!(capability = tgetstr(cap, NULL)))
	{
		ft_putendl_fd("ft_select: Failed to load capability string", 2);
		exit(1);
	}
	return (capability);
}

void	put_cap(char *cap)
{
 	char	*cap_string;
 	int	(*fptr)(int);

 	cap_string = get_capstring(cap);
 	fptr = ft_puts;
 	tputs(cap_string, 1, fptr);
}
