/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:14:30 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/02 14:54:14 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		line_check(size_t line_length)
{
	int		height;
	int		width;
	char	**dest;

	if ((width = tgetnum("co")) == -1 ||
	(height = tgetnum("li") == -1))
	{
		ft_putendl_fd("ft_select: termcap database unreachable", 2);
		exit(1);
	}
	if (!(dest = (char **)malloc(sizeof(char *))))
	{
		ft_putendl_fd("ft_select: Too few memory available, abort.", 2);
		exit(1);
	}
	if (height < 1)
		return (-1);
	if (line_length > (size_t)width)
		return (1);
	return (0);
}

size_t	get_line_size(t_list *entries)
{
	size_t	total_size;
	t_list	*tmp;

	total_size = ft_strlen(entries->content);
	tmp = entries->next;
	while (tmp != entries)
	{
		total_size += ft_strlen(tmp->content);
		total_size++;
		tmp = tmp->next;
	}
	return (total_size);
}
