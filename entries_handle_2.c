/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entries_handle_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 11:27:36 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/11 15:38:44 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int		another_one_selected(t_list *entries)
{
	t_list		*tmp;

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

static void		entry_return_one(t_list *entries)
{
	ft_putstr_fd(ENT->value, STDOUT_FILENO);
	if (another_one_selected(entries))
		ft_putchar_fd(' ', STDOUT_FILENO);
	ENT->selected = 0;
}

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
	ft_putchar('\n');
	free_all_entries(entries);
}
