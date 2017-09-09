/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:21:04 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/09 18:51:44 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_all	*g_all;

static void		handle_input(char *buffer, t_all *usef)
{
	if (*(unsigned int*)buffer == 27)
		term_rollback();
	if (buffer[0] == 10)
		return_entries(usef->elems);
	if (buffer[0] == 127)
		usef->elems = remove_one(usef->elems);
	if (buffer[0] == 27 && buffer[2] == 68)
		cursor_on_prev(usef->elems);
	if (buffer[0] == 27 && buffer[2] == 67)
		cursor_on_next(usef->elems);
	if (buffer[0] == 32)
		select_cur(usef->elems);
}

static int		main_loop(t_all *usef)
{
	char		*buffer;

	buffer = strgen(5);
	sigaction_handler();
	while (42)
	{
		push_cap("cl");
		if (!line_check(usef))
			display_entries(usef);
		ft_bzero(buffer, 4);
		read(STDIN_FILENO, buffer, 4);
		handle_input(buffer, usef);
		ft_bzero(buffer, 5);
	}
	return (0);
}

int				main(int argc, char **argv)
{
	t_list		*entries;
	t_all		*usef;

	if (argc <= 1)
	{
		write(STDERR_FILENO, "usage: ./ft_select [arguments ...]\n",
		sizeof("usage: ./ft_select [arguments ...]\n"));
		exit(1);
	}
	init_checks();
	load_term_struct();
	entries = get_entries(argv);
	usef = all_struct_init(entries);
	if (setting_term())
		exit(1);
	((t_elem *)(entries->content))->cursor = 1;
	main_loop(usef);
	return (0);
}
