/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:14:30 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/05 16:03:27 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int				line_check(t_all *usef)
{
	int			term_lines;
	int			term_cols;

	usef->d_infos = display_info(usef);
	term_lines = get_term_size("lines");
	term_cols = get_term_size("cols");
	if (usef->d_infos->lines_needed > term_lines)
		return (-1);
	return (0);
}

static int		word_per_line(char **entries_array)
{
	int			word_nb;
	size_t		term_cols;
	size_t		wordstack;
	size_t		largest;

	wordstack = 1;
	largest = ft_strlen(*entries_array) + 1;
	wordstack += largest;
	term_cols = get_term_size("cols");
	if (wordstack > term_cols)
		return (-1);
	word_nb = 1;
	while (*entries_array)
	{
		wordstack += largest;
		if (wordstack > term_cols)
			return (word_nb);
		word_nb++;
		entries_array++;
	}
	return (word_nb);
}

size_t			get_line_size(t_list *entries)
{
	size_t		total_size;
	t_list		*tmp;

	total_size = ft_strlen(entries->content);
	tmp = entries->next;
	while (tmp != entries)
	{
		total_size += ft_strlen(tmp->content);
		total_size++;
		tmp = tmp->next;
	}
	return (total_size);
}

t_printinfo		*display_info(t_all *usef)
{
	char		**tmp;
	t_printinfo	*dest;

	if (!(dest = (t_printinfo *)malloc(sizeof(t_printinfo))))
	{
		write(STDERR_FILENO, "ft_select: malloc error, abort.\n",
		sizeof("ft_select: malloc error, abort.\n"));
		exit(1);
	}
	tmp = usef->sorted_array;
	dest->largest_word = ft_strlen(*tmp) + 1;
	dest->nb_word = word_per_line(tmp);
	tmp = usef->sorted_array;
	if (!(ft_tab_size(tmp) % dest->nb_word))
		dest->lines_needed = ft_tab_size(tmp) / dest->nb_word;
	dest->lines_needed = (ft_tab_size(tmp) / dest->nb_word) + 1;
	return (dest);
}
