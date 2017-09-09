/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 09:59:11 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/09 19:13:58 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		term_rollback(void)
{
	if (tcsetattr(0, TCSANOW, &g_term) == -1)
		ft_putendl_fd("ft_select: failed to apply changes on term", 2);
	push_cap("ve");
	push_cap("te");
	exit(0);
}

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
		term_rollback();
	if (sig == SIGCONT)
		setting_term();
	if (sig == SIGQUIT)
		term_rollback();
	if (sig == SIGWINCH)
		push_cap("cl");
}

void		sigaction_handler(void)
{
	struct sigaction action;

	bzero(&action, sizeof(action));
	action.sa_handler = &sig_handler;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGCONT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
	sigaction(SIGWINCH, &action, NULL);
}
