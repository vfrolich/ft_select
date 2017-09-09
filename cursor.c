/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 11:15:10 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/09 10:35:12 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	cursor_on_next(t_list *entries)
{
	while (((t_elem *)(entries->content))->cursor != 1)
		entries = entries->next;
	((t_elem *)(entries->content))->cursor = 0;
	entries = entries->next;
	((t_elem *)(entries->content))->cursor = 1;
}

void	cursor_on_prev(t_list *entries)
{
	t_list	*elem;

	while (((t_elem *)(entries->content))->cursor != 1)
		entries = entries->next;
	elem = entries;
	((t_elem *)(elem->content))->cursor = 0;
	while (elem->next != entries)
		elem = elem->next;
	((t_elem *)(elem->content))->cursor = 1;
}

void	select_cur(t_list *entries)
{
	while (((t_elem *)(entries->content))->cursor != 1)
		entries = entries->next;
	if (((t_elem *)(entries->content))->selected == 0)
	{
		((t_elem *)(entries->content))->selected = 1;
		cursor_on_next(entries);
	}
	else
		((t_elem *)(entries->content))->selected = 0;
}
