/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:20:03 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/11 16:20:27 by vfrolich         ###   ########.fr       */
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

void				display_entries(t_all *container)
{
	t_list			*tmp;
	int				nb_words;

	if (line_check(container) == -1)
		return ;
	tmp = container->elems;
	display_one(tmp, container->d_infos->largest_word, container->fd);
	tmp = tmp->next;
	nb_words = 1;
	while (tmp != container->elems)
	{
		while (nb_words < container->d_infos->nb_word
			&& tmp != container->elems)
		{
			display_one(tmp, container->d_infos->largest_word, container->fd);
			tmp = tmp->next;
			nb_words++;
		}
		ft_putchar_fd('\n', container->fd);
		nb_words = 0;
	}
}

size_t				get_term_size(char *field)
{
	struct winsize	win;

	ft_bzero(&win, sizeof(win));
	if (ioctl(STDIN_FILENO, TIOCGSIZE, &win) == -1)
	{
		write(STDERR_FILENO, "ft_select: unable to get terminal size\n",
			sizeof("ft_select: unable to get terminal size\n"));
		return (0);
	}
	if (!ft_strcmp(field, "lines"))
		return (win.ws_row);
	return (win.ws_col);
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
