/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:20:03 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/03 08:01:38 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	display_one(t_list *elem)
{
	if (((t_elem *)(elem->content))->cursor == 1 &&
		((t_elem *)(elem->content))->selected == 1)
		underlined_inversed(((t_elem *)(elem->content))->value);
	else if (((t_elem *)(elem->content))->cursor == 1)
		ft_underliner(((t_elem *)(elem->content))->value);
	else if (((t_elem *)(elem->content))->selected == 1)
		inversed_video(((t_elem *)(elem->content))->value);
	else
		ft_putstr(((t_elem *)(elem->content))->value);
}

void	display_entries(t_list *elem)
{
	t_list	*tmp;

	tmp = elem;
	display_one(elem);
	tmp = tmp->next;
	while (tmp != elem)
	{
		ft_putchar(' ');
		display_one(tmp);
		tmp = tmp->next;
	}
	ft_putchar('\n');
}
