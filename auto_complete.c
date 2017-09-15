/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 11:42:28 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/15 15:46:34 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		select_new_entry(t_list *entries, t_list *to_select)
{
	t_list	*tmp;

	tmp = entries;
	while (((t_elem *)(tmp->content))->cursor != 1)
		tmp = tmp->next;
	((t_elem *)(tmp->content))->cursor = 0;
	((t_elem *)(to_select->content))->cursor = 1;
}

static int		dyna_search(t_list *entries, char *buffer, int c_read)
{
	t_list	*tmp;

	tmp = entries;
	if (!c_read)
		return (1);
	if (!ft_strncmp(((t_elem *)(tmp->content))->value, buffer, c_read))
	{
		select_new_entry(entries, tmp);
		return (0);
	}
	tmp = tmp->next;
	while (tmp != entries)
	{
		if (!ft_strncmp(((t_elem *)(tmp->content))->value, buffer, c_read))
		{
			select_new_entry(entries, tmp);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void			read_for_search(t_list *entries, char *oldbuff)
{
	char		*buffer;
	char		*to_search;
	char		*tmp;
	int			ret;

	if (*oldbuff != 9)
		return ;
	buffer = strgen(132);
	to_search = strgen(1);
	tmp = NULL;
	ret = 1;
	while (!ft_strchr(buffer, 9))
	{
		ret = ret + read(STDIN_FILENO, buffer, 1);
		tmp = ft_strdup(buffer);
		to_search = ft_strjoin_free(&to_search, &tmp);
		dyna_search(entries, to_search, ret - 1);
	}
	dyna_search(entries, to_search, ret - 1);
	ft_strdel(&buffer);
	ft_strdel(&to_search);
}
