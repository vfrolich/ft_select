/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entries_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 10:20:02 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/11 16:08:38 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		free_entry(t_list *entry)
{
	ft_strdel(&((t_elem *)(entry->content))->value);
	free(entry->content);
	free(entry);
}

static t_list	*go_to_prev(t_list *entries)
{
	t_list		*prev;

	prev = entries->next;
	while (prev->next != entries)
		prev = prev->next;
	return (prev);
}

void			free_all_entries(t_list *entries)
{
	t_list	*tmp;
	t_list	*to_free;

	tmp = entries;
	tmp = entries->next;
	while (tmp != entries)
	{
		to_free = tmp;
		tmp = tmp->next;
		free_entry(to_free);
	}
	free_entry(tmp);
}

t_list			*remove_one(t_list *entries)
{
	t_list		*prev;
	t_list		*tmp;
	t_list		*origin;

	if (entries == entries->next)
		term_rollback(0);
	origin = entries;
	tmp = entries;
	prev = entries->next;
	prev = go_to_prev(entries);
	while (((t_elem *)(tmp->content))->cursor != 1)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	entries = tmp->next;
	((t_elem *)(entries->content))->cursor = 1;
	prev->next = entries;
	if (origin != tmp)
	{
		free_entry(tmp);
		return (origin);
	}
	free_entry(tmp);
	return (entries);
}
