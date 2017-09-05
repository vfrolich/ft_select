/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:20:03 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/05 16:10:58 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	display_one(t_list *elem, int largest_word)
{
	int	padding;

	if (((t_elem *)(elem->content))->cursor == 1 &&
		((t_elem *)(elem->content))->selected == 1)
		underlined_inversed(((t_elem *)(elem->content))->value);
	else if (((t_elem *)(elem->content))->cursor == 1)
		ft_underliner(((t_elem *)(elem->content))->value);
	else if (((t_elem *)(elem->content))->selected == 1)
		inversed_video(((t_elem *)(elem->content))->value);
	else
		ft_putstr(((t_elem *)(elem->content))->value);
	padding = largest_word - ft_strlen(((t_elem *)(elem->content))->value);
	while (padding > 0)
	{
		ft_putchar(' ');
		padding--;
	}
}

void	display_entries(t_all *usef)
{
	t_list	*tmp;
	int		nb_words;

	tmp = usef->elems;
	display_one(tmp, usef->d_infos->largest_word);
	tmp = tmp->next;
	nb_words = 1;
	while (tmp != usef->elems)
	{
		while (nb_words < usef->d_infos->nb_word && tmp != usef->elems)
		{
			display_one(tmp, usef->d_infos->largest_word);
			tmp = tmp->next;
			nb_words++;
		}
		ft_putchar('\n');
		nb_words = 0;
	}
}
