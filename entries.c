/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entries.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 10:20:02 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/08 16:08:10 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void			return_entries(t_list *entries)
{
	t_list		*tmp;

	tmp = entries;
	if (tcsetattr(0, TCSANOW, &g_term) == -1)
		ft_putendl_fd("ft_select: failed to apply changes on term", 2);
	push_cap("ve");
	push_cap("te");
	if (ENT->selected)
		entry_return_one(entries);
	entries = entries->next;
	while (entries != tmp)
	{
		if (ENT->selected)
			entry_return_one(entries);
		entries = entries->next;
	}
	exit(0);
}

t_list			*get_entries(char **argv)
{
	t_list		*head;
	t_list		*new;
	char		**tmp;

	tmp = argv;
	tmp++;
	head = entry_init_one(*tmp);
	tmp++;
	while (*tmp)
	{
		if (**tmp)
		{
			new = entry_init_one(*tmp);
			lst_add(new, &head);
		}
		tmp++;
	}
	if (!head->next)
		head->next = head;
	else
		new->next = head;
	return (head);
}

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

t_list			*remove_one(t_list *entries)
{
	t_list		*prev;
	t_list		*tmp;
	t_list		*origin;

	if (entries == entries->next)
		term_rollback();
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
