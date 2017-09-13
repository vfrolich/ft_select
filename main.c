/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:21:04 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/13 21:09:24 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		handle_input(char *buffer, t_all *container)
{
	if (*(unsigned int*)buffer == 27)
	{
		free_all_entries(container->elems);
		free_all_t(container);
		term_rollback(0);
	}
	if (buffer[0] == 10)
	{
		return_entries(container->elems);
		free_all_t(container);
		exit(0);
	}
	if (buffer[0] == 127)
		container->elems = remove_one(container->elems);
	if (buffer[0] == 27 && buffer[2] == 68)
		cursor_on_prev(container->elems);
	if (buffer[0] == 27 && buffer[2] == 67)
		cursor_on_next(container->elems);
	if (buffer[0] == 32)
		select_cur(container->elems);
}

static int		main_loop(t_all *container)
{
	char		*buffer;

	buffer = strgen(5);
	while (42)
	{
		sigaction_handler();
		push_cap("cl");
		display_entries(container);
		ft_bzero(buffer, 4);
		read(STDIN_FILENO, buffer, 4);
		handle_input(buffer, container);
		ft_bzero(buffer, 5);
	}
	return (0);
}

int				main(int argc, char **argv)
{
	t_list		*entries;
	t_all		*container;

	if (argc <= 1)
	{
		write(STDERR_FILENO, "usage: ./ft_select [arguments ...]\n",
		sizeof("usage: ./ft_select [arguments ...]\n"));
		exit(1);
	}
	init_checks();
	load_term_struct();
	entries = get_entries(argv);
	container = all_struct_init(entries);
	if (setting_term())
		exit(1);
	((t_elem *)(entries->content))->cursor = 1;
	get_file_type(entries);
	main_loop(container);
	return (0);
}
