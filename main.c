/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:21:04 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/14 14:39:47 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int		remove_ent(t_list *entries)
{
	if (entries == entries->next)
	{
		free_entry(entries);
		push_cap("te");
		return (0);
	}
	return (2);
}

static int		handle_input(char *buffer, t_all *container)
{
	if (*(unsigned int*)buffer == 27)
	{
		push_cap("te");
		free_all_entries(container->elems);
		return (0);
	}
	if (buffer[0] == 10)
	{
		return_entries(container->elems);
		return (0);
	}
	if (buffer[0] == 127)
	{
		if (remove_ent(container->elems) == 2)
			container->elems = remove_one(container->elems);
		else
			return (0);
	}
	if (buffer[0] == 27 && buffer[2] == 68)
		cursor_on_prev(container->elems);
	if (buffer[0] == 27 && buffer[2] == 67)
		cursor_on_next(container->elems);
	if (buffer[0] == 32)
		select_cur(container->elems);
	return (2);
}

static int		main_loop(t_all *container)
{
	char		*buffer;
	int			ret;

	buffer = strgen(5);
	ret = 1;
	while (42)
	{
		sigaction_handler();
		push_cap("cl");
		display_entries(container);
		ft_bzero(buffer, 4);
		read(STDIN_FILENO, buffer, 4);
		ret = handle_input(buffer, container);
		if (!ret)
		{
			ft_strdel(&buffer);
			free_all_t(container);
			return (0);
		}
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
	if (tcsetattr(0, TCSANOW, &g_term) == -1)
		ft_putendl_fd("ft_select: failed to apply changes on term", 2);
	push_cap("ve");
	return (0);
}
