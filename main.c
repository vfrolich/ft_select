/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:21:04 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/08 15:39:51 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		screen_clear(t_printinfo *infos)
{
	int		i;

	i = 0;
	while (i <= infos->lines_needed)
	{
		push_cap("dl");
		push_cap("up");
		i++;
	}
}

void		handle_input(char *buffer, t_all *usef)
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

int			main_loop(t_all *usef)
{
	char	*buffer;

	buffer = strgen(5);
	push_cap("cr");
	while (42)
	{
		screen_clear(usef->d_infos);
		if (!line_check(usef))
			display_entries(usef);
		all_signal_handler();
		buffer = read_input(buffer);
		handle_input(buffer, usef);
		ft_strclr(buffer);
	}
	return (0);
}

int			main(int argc, char **argv)
{
	t_list	*entries;
	t_all	*usef;

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
