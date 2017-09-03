/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entries.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 10:20:02 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/03 13:02:46 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

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

void		return_entries(t_list *entries)
{
	t_list	*tmp;

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

t_list		*get_entries(char **argv)
{
	t_list	*head;
	t_list	*new;

	argv++;
	head = entry_init_one(*argv);
	argv++;
	while (*argv)
	{
		if (**argv)
		{
			new = entry_init_one(*argv);
			lst_add(new, &head);
		}
		argv++;
	}
	if (!head->next)
		head->next = head;
	else
		new->next = head;
	return (head);
}

static void	free_entry(t_list *entry)
{
	ft_strdel(&((t_elem *)(entry->content))->value);
	free(entry->content);
	free(entry);
}

int			remove_one(t_list **entries)
{
	t_list	*prev;
	t_list	*tmp;

	if (!*entries)
		return (1);
	tmp = *entries;
	if (tmp == tmp->next)
	{
		free_entry(tmp);
		return (1);
	}
	prev = tmp;
	while (prev->next != tmp)
		prev = prev->next;
	prev->next = tmp->next;
	*entries = tmp->next;
	cursor_on_next(tmp);
	free_entry(tmp);
	return (0);
}
