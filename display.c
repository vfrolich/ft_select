/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:20:03 by vfrolich          #+#    #+#             */
/*   Updated: 2017/08/25 19:25:10 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		display_one(t_list	*entry)
{
	if (((t_entry *)ARG)->cursor == 1)
	{
		ft_putstr("word cursored->");
		underline_word(((t_entry *)ARG)->value);
	}
	else
		ft_putstr(((t_entry *)ARG)->value);
}
void		entries_display(t_list *entry)
{
	t_list	*tmp;

	tmp = entry;
	display_one(tmp);
	if (entry->next != tmp)
		ft_putchar(' ');
	tmp = tmp->next;
	while (tmp != entry)
	{
		display_one(tmp);
		if (tmp->next != entry)
			ft_putchar(' ');
		tmp = tmp->next;
	}
}
