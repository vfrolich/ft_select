/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 16:37:30 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/05 16:00:15 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

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

int					setting_term(void)
{
	struct termios	term;

	if (tgetent(NULL, getenv("TERM")) == -1)
	{
		write(STDERR_FILENO, "tgetent\n", sizeof("tgetent\n"));
		exit(1);
	}
	if (tcgetattr(0, &term) == -1)
	{
		ft_putendl_fd("ft_select: failed to load termios struct", 2);
		return (1);
	}
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	push_cap("ti");
	push_cap("ho");
	push_cap("vi");
	if (tcsetattr(0, TCSANOW, &term) == -1)
		ft_putendl_fd("ft_select: failed to apply changes on term", 2);
	return (0);
}

void				load_term_struct(void)
{
	ft_bzero(&g_term, sizeof(struct termios));
	if (tcgetattr(0, &g_term) == -1)
	{
		ft_putendl_fd("ft_select: failed to load termios struct, abort", 2);
		exit(1);
	}
	if (tcgetattr(0, &g_term) == -1)
	{
		ft_putendl_fd("ft_select: failed to load termios struct, abort", 2);
		exit(1);
	}
}

t_all				*all_struct_init(t_list *entries)
{
	t_all			*dest;

	if (!(dest = (t_all *)malloc(sizeof(t_all))))
	{
		write(STDERR_FILENO, "ft_select: malloc error, abort.\n",
		sizeof("ft_select: unable to get term size, abort\n"));
		exit(1);
	}
	dest->elems = entries;
	dest->sorted_array = entries_array(dest);
	dest->d_infos = display_info(dest);
	return (dest);
}
