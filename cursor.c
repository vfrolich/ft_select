/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 11:15:10 by vfrolich          #+#    #+#             */
/*   Updated: 2017/08/24 02:18:36 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		ft_puts(int n)
{
	char c;

	if (n < 0)
		return (-1);
	c = (char)n;
	ft_putchar(c);
	return (0);
}

void	cursor_on_entries()
{
	// size_t line_length;

	// line_lenght = get_line_size(entries);
	char	*capa;	
	int 	(*fptr)(int);

	capa = get_capstring("cr");
	fptr = ft_puts;
	tputs(capa, 1, fptr);
}

void	cursor_on_next(t_list *entry)
{
		t_list	*tmp;

		tmp = entry;
		((t_entry *)tmp->content)->cursor = 0;
		tmp = tmp->next;
		((t_entry *)tmp->content)->cursor = 1;
}

void	cursor_on_prev(t_list *entry)
{
	t_list	*tmp;

	tmp = entry;
	((t_entry *)tmp->content)->cursor = 0;
	while (tmp->next != entry)
		tmp = tmp->next;
	((t_entry *)tmp->content)->cursor = 1;	
}