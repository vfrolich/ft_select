/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:14:30 by vfrolich          #+#    #+#             */
/*   Updated: 2017/08/08 17:21:43 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

char	*line_feed(char *line, t_list *entries, size_t strlenght)
{
	char *tmp;
	
	while (strlenght)
	{
		tmp = entries->content;
		while (*tmp && strlenght)
		{
			*line = *tmp;
			strlenght--;
			tmp++;
			line++;
		}
		if (strlenght)
		{
			*line = ' ';
			line++;
			strlenght--;
		}
		else
			return (line);
		entries = entries->next;
	}
	return (line);
}

char	*line_init(t_list *entries)
{
	size_t	line_size;
	char 	*ptr;
	char	*line;
	t_list	*tmp;

	// if ((cols = tgetnum("co")) == - 1)
	// 	return (NULL);
	// if (!(line = ft_strnew(cols)))
	// {
	// 	ft_putendl_fd("ft_select: no memory\
	// 	available for line buff, abort.", 2);
	// 	exit(1);
	// }
	line_size = get_line_size(entries);
	if (!(line = ft_strnew(line_size)))
	{
		ft_putendl_fd("ft_select: no memory\
		available for line buff, abort.", 2);
		exit(1);
	}
	ptr = line;
	tmp = entries;
	line = line_feed(line, tmp, line_size);
	line = ptr;
	return (line);
}

size_t	get_line_size(t_list *entries)
{
	size_t 	total_size;
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
