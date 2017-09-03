/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 09:59:11 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/03 11:27:03 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	term_rollback(void)
{
	if (tcsetattr(0, TCSANOW, &g_term) == -1)
		ft_putendl_fd("ft_select: failed to apply changes on term", 2);
	push_cap("ve");
	push_cap("te");
	exit(0);
}

void	all_signal_handler(void)
{
	void	(*fptr)(int);

	fptr = sig_handler;
	signal(SIGINT, fptr);
	signal(SIGCONT, fptr);
	signal(SIGQUIT, fptr);
	signal(SIGWINCH, fptr);
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
		term_rollback();
	if (sig == SIGCONT)
		setting_term();
	if (sig == SIGQUIT)
		term_rollback();
	if (sig == SIGWINCH)
	{
		term_rollback();
		exit(0);
	}
}
