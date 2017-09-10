/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:14:30 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/10 10:37:11 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int				line_check(t_all *usef)
{
	size_t			term_lines;
	size_t			term_cols;

	if (usef->d_infos != NULL)
		free(usef->d_infos);
	usef->d_infos = display_info(usef);
	term_lines = get_term_size("lines");
	term_cols = get_term_size("cols");
	if (!term_lines || !term_cols)
		return (-1);
	if ((size_t)usef->d_infos->lines_needed > term_lines)
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
