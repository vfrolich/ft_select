/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 09:59:11 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/14 14:34:04 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		term_rollback(int ret)
{
	if (tcsetattr(0, TCSANOW, &g_term) == -1)
		ft_putendl_fd("ft_select: failed to apply changes on term", 2);
	push_cap("ve");
	push_cap("te");
	if (ret)
		exit(ret);
}

static void	sig_tstp_handler(void)
{
	char	input[2];

	input[0] = g_term.c_cc[VSUSP];
	input[1] = 0;
	push_cap("ve");
	push_cap("te");
	if (tcsetattr(0, TCSANOW, &g_term) == -1)
		ft_putendl_fd("ft_select: failed to apply changes on term", 2);
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, input);
}

static void	sig_handler(int sig)
{
	if (sig == SIGCONT)
		setting_term();
	else if (sig == SIGWINCH)
		push_cap("cl");
	else if (sig == SIGTSTP)
		sig_tstp_handler();
	else
		term_rollback(1);
}

static void	sigaction_handle_2(void)
{
	struct sigaction action;

	bzero(&action, sizeof(action));
	action.sa_handler = &sig_handler;
	sigaction(SIGXFSZ, &action, NULL);
	sigaction(SIGVTALRM, &action, NULL);
	sigaction(SIGPROF, &action, NULL);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
}

void		sigaction_handler(void)
{
	struct sigaction action;

	bzero(&action, sizeof(action));
	action.sa_handler = &sig_handler;
	sigaction(SIGTSTP, &action, NULL);
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGCONT, &action, NULL);
	sigaction(SIGWINCH, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
	sigaction(SIGHUP, &action, NULL);
	sigaction(SIGILL, &action, NULL);
	sigaction(SIGSEGV, &action, NULL);
	sigaction(SIGTRAP, &action, NULL);
	sigaction(SIGABRT, &action, NULL);
	sigaction(SIGFPE, &action, NULL);
	sigaction(SIGEMT, &action, NULL);
	sigaction(SIGBUS, &action, NULL);
	sigaction(SIGSYS, &action, NULL);
	sigaction(SIGPIPE, &action, NULL);
	sigaction(SIGALRM, &action, NULL);
	sigaction(SIGTERM, &action, NULL);
	sigaction(SIGTTIN, &action, NULL);
	sigaction(SIGTTOU, &action, NULL);
	sigaction(SIGXCPU, &action, NULL);
	sigaction_handle_2();
}
