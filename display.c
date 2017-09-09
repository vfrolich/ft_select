/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:20:03 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/09 12:27:51 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void			display_one(t_list *elem, int largest_word)
{
	int				padding;

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

void				display_entries(t_all *usef)
{
	t_list			*tmp;
	int				nb_words;

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

void				screen_clear(t_printinfo *infos)
{
	int				i;

	i = 0;
	while (i <= infos->lines_needed)
	{
		push_cap("dl");
		push_cap("up");
		i++;
	}
}

size_t				get_term_size(char *field)
{
	struct ttysize	w;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
	{
		write(STDERR_FILENO, "ft_select: unable to get term size, abort\n",
		sizeof("ft_select: unable to get term size, abort\n"));
		exit(1);
	}
	if (!ft_strcmp(field, "lines"))
		return (w.ts_lines);
	return (w.ts_cols);
}

void				push_cap(char *const cap)
{
	char			*str;

	str = tgetstr(cap, NULL);
	if (str)
		write(STDOUT_FILENO, str, ft_strlen(str));
	else
		write(STDERR_FILENO, "cap error\n", sizeof("cap error\n"));
}
