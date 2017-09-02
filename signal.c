/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 09:59:11 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/02 14:24:55 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	term_rollback(struct termios term)
{
	if (tcsetattr(0, TCSANOW, &term) == -1)
		ft_putendl_fd("ft_select: failed to apply changes on term", 2);
	tputs(tgetstr("ve", NULL), 0, ft_puts);
	push_cap("te");
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
		exit(0);
}
