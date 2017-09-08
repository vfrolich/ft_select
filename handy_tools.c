/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handy_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:17:49 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/08 16:07:32 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

char		*read_input(char *buffer)
{
	ft_bzero(buffer, 4);
	read(0, buffer, 4);
	return (buffer);
}

char		*strgen(size_t lenght)
{
	char	*line;

	if (!(line = ft_strnew(lenght)))
	{
		ft_putendl_fd("ft_select: no memory	available for line buf, need: ", 2);
		ft_putendl_fd(" abort.", 2);
		exit(1);
	}
	return (line);
}

int			another_one_selected(t_list *entries)
{
	t_list	*tmp;

	tmp = entries;
	tmp = tmp->next;
	while (tmp != entries)
	{
		if (((t_elem *)(tmp->content))->selected)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void		entry_return_one(t_list *entries)
{
	ft_putstr_fd(ENT->value, STDOUT_FILENO);
	if (another_one_selected(entries))
		ft_putchar_fd(' ', STDOUT_FILENO);
	ENT->selected = 0;
}

size_t		count_entries(t_list *entries)
{
	t_list	*tmp;
	size_t	count;

	tmp = entries;
	count = 1;
	tmp = tmp->next;
	while (tmp != entries)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}
