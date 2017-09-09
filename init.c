/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:20:21 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/09 18:07:01 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static t_list	*entry_init_one(char *arg)
{
	t_elem		*entry;
	t_list		*dest;

	if (!(entry = (t_elem *)malloc(sizeof(t_elem))))
	{
		ft_putendl_fd("ft_select: malloc error", 2);
		exit(1);
	}
	entry->value = strgen(ft_strlen(arg));
	entry->value = ft_strcpy(entry->value, arg);
	entry->cursor = 0;
	entry->selected = 0;
	if (!(dest = ft_lstnew(entry, sizeof(entry))))
	{
		ft_putendl_fd("ft_select: malloc error", 2);
		exit(1);
	}
	free(entry);
	return (dest);
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

t_all			*all_struct_init(t_list *entries)
{
	t_all		*dest;
	char		*name;
	int			fd;

	if (!(dest = (t_all *)malloc(sizeof(t_all))))
	{
		write(STDERR_FILENO, "ft_select: malloc error, abort.\n",
		sizeof("ft_select: unable to get term size, abort\n"));
		exit(1);
	}
	dest->elems = entries;
	dest->sorted_array = entries_array(dest);
	dest->d_infos = display_info(dest);
	if (!isatty(1))
	{
		name = ttyname(0);
		fd = open(name, O_WRONLY);
		dest->fd = fd;
	}
	else
		dest->fd = STDIN_FILENO;
	return (dest);
}
