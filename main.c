/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:21:04 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/02 15:58:53 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	handle_input(char *buffer, t_all *usef)
{
	if (*(unsigned int*)buffer == 27)
	{
		term_rollback(usef->term);
		exit(0);
	}
	if (buffer[0] == 127)
	{
		if (remove_one(&usef->elems))
		{
			term_rollback(usef->term);
			exit(0);
		}
	}
	if (buffer[0] == 27 && buffer[2] == 68)
		cursor_on_prev(usef->elems);
	if (buffer[0] == 27 && buffer[2] == 67)
		cursor_on_next(usef->elems);
	if (buffer[0] == 32)
		select_cur(usef->elems);
}

int		main_loop(t_all *usef)
{
	char	*buffer;

	buffer = strgen(5);
	while (42)
	{
		push_cap("cr");
		tputs(tgetstr("dl", NULL), 1, ft_puts);
		display_entries(usef->elems);
		tputs(tgetstr("up", NULL), 1, ft_puts);
		buffer = read_input(buffer);
		handle_input(buffer, usef);
	}
	return (0);
}

t_all	*all_init(t_list *entries)
{
	t_all			*dest;
	struct termios	termi;

	dest = (t_all *)malloc(sizeof(t_all));
	termi = get_term_struct();
	dest->term = termi;
	dest->elems = entries;
	if ((dest->co = tgetnum("co")) == ERR)
		write(STDERR_FILENO, "cap error\n", sizeof("cap error\n"));
	if ((dest->li = tgetnum("li")) == ERR)
		write(STDERR_FILENO, "cap error\n", sizeof("cap error\n"));
	return (dest);
}

int		main(int argc, char **argv)
{
	t_list			*entries;
	void			(*fptr)	(int);
	t_list			*tmp;
	struct termios	term;
	t_all			*usef;

	fptr = sig_handler;
	signal(SIGINT, fptr);
	init_checks();
	term = get_term_struct();
	entries = get_entries(argv);
	usef = all_init(entries);
	if (setting_term())
		exit(1);
	if (argc > 1)
	{
		tmp = entries;
		((t_elem *)(entries->content))->cursor = 1;
		main_loop(usef);
	}
	return (0);
}
