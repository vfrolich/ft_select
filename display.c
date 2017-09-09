/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:20:03 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/09 19:08:59 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void			display_one(t_list *elem, int largest_word, int fd)
{
	int				padding;

	if (((t_elem *)(elem->content))->cursor == 1 &&
		((t_elem *)(elem->content))->selected == 1)
		underlined_inversed(((t_elem *)(elem->content))->value, fd);
	else if (((t_elem *)(elem->content))->cursor == 1)
		ft_underliner(((t_elem *)(elem->content))->value, fd);
	else if (((t_elem *)(elem->content))->selected == 1)
		inversed_video(((t_elem *)(elem->content))->value, fd);
	else
		ft_putstr_fd(((t_elem *)(elem->content))->value, fd);
	padding = largest_word - ft_strlen(((t_elem *)(elem->content))->value);
	while (padding > 0)
	{
		ft_putchar_fd(' ', fd);
		padding--;
	}
}

void				display_entries(t_all *usef)
{
	t_list			*tmp;
	int				nb_words;

	tmp = usef->elems;
	display_one(tmp, usef->d_infos->largest_word, usef->fd);
	tmp = tmp->next;
	nb_words = 1;
	while (tmp != usef->elems)
	{
		while (nb_words < usef->d_infos->nb_word && tmp != usef->elems)
		{
			display_one(tmp, usef->d_infos->largest_word, usef->fd);
			tmp = tmp->next;
			nb_words++;
		}
		ft_putchar_fd('\n', usef->fd);
		nb_words = 0;
	}
}

size_t				get_term_size(char *field)
{
	struct ttysize	w;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) == -1)
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
	char			*tty_name;
	int				fd;

	tty_name = NULL;
	if (!isatty(1))
	{
		tty_name = ttyname(0);
		fd = open(tty_name, O_WRONLY);
	}
	str = tgetstr(cap, NULL);
	if (str)
	{
		if (!tty_name)
			write(STDOUT_FILENO, str, ft_strlen(str));
		else
		{
			write(fd, str, ft_strlen(str));
			close(fd);
		}
	}
	else
		write(STDERR_FILENO, "cap error\n", sizeof("cap error\n"));
}
