/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 16:37:30 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/02 14:27:05 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int				setting_term(void)
{
	struct termios	term;

	if (tgetent(NULL, getenv("TERM")) == -1)
	{
		write(STDERR_FILENO, "tgetent\n", sizeof("tgetent\n"));
		abort();
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

struct termios	get_term_struct(void)
{
	struct termios	term;

	ft_bzero(&term, sizeof(struct termios));
	if (tcgetattr(0, &term) == -1)
	{
		ft_putendl_fd("ft_select: failed to load termios struct, abort", 2);
		exit(1);
	}
	if (tcgetattr(0, &term) == -1)
	{
		ft_putendl_fd("ft_select: failed to load termios struct, abort", 2);
		exit(1);
	}
	return (term);
}
