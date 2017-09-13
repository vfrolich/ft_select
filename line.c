/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:14:30 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/11 16:14:29 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int				line_check(t_all *container)
{
	size_t			term_lines;
	size_t			term_cols;

	if (container->d_infos != NULL)
		free(container->d_infos);
	container->d_infos = display_info(container);
	term_lines = get_term_size("lines");
	term_cols = get_term_size("cols");
	if (!term_lines || !term_cols || !container->d_infos->nb_word)
		return (-1);
	if ((size_t)container->d_infos->lines_needed > term_lines)
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
		return (0);
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

t_printinfo		*display_info(t_all *container)
{
	char		**tmp;
	t_printinfo	*dest;

	dest = NULL;
	if (!(dest = (t_printinfo *)malloc(sizeof(t_printinfo))))
	{
		write(STDERR_FILENO, "ft_select: malloc error, abort.\n",
		sizeof("ft_select: malloc error, abort.\n"));
		exit(1);
	}
	tmp = container->sorted_array;
	dest->largest_word = ft_strlen(*tmp) + 1;
	dest->nb_word = word_per_line(tmp);
	if (dest->nb_word == 0)
		return (dest);
	tmp = container->sorted_array;
	if (!(ft_tab_size(tmp) % dest->nb_word))
		dest->lines_needed = ft_tab_size(tmp) / dest->nb_word;
	dest->lines_needed = (ft_tab_size(tmp) / dest->nb_word) + 1;
	dest->lines_needed += 2;
	return (dest);
}
