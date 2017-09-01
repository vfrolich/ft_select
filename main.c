/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:21:04 by vfrolich          #+#    #+#             */
/*   Updated: 2017/08/26 17:25:55 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	read_lul(char *str)
{
	int i;

	i = 0;
	while (i <= 8 && str[1] != '\n')
	{
		ft_putnbr(str[i]);
		ft_putchar(' ');
		i++;
	}
}

void	dummy_print(t_list *elem)
{
	t_list	*tmp;

	tmp = elem;
	ft_putstr("elem -> ");
	ft_putendl((((t_entry *)elem->content)->value));
	ft_putstr("selected -> ");
	ft_putnbrendl((((t_entry *)elem->content)->selected));
	tmp = tmp->next;
	while (tmp != elem)
	{
		ft_putstr("elem -> ");
		ft_putendl((((t_entry *)elem->content)->value));
		ft_putstr("selected -> ");
		ft_putnbrendl((((t_entry *)elem->content)->selected));
		tmp = tmp->next;
	}
}

int main(int argc, char **argv, char **environ)
{
	t_list 	*entries;
	// char	*line;
	size_t	line_length;
	char 	*lol;

	if (argc > 1)
	{
		entries = get_entries(argv);
		init_checks(environ);
		term_init();
		line_length = get_line_size(entries);
		lol = strgen(4);
		((t_entry *)(entries->content))->cursor = 1;
		// put_cap("vi");
		while (42)
		{
			dummy_print(entries);
			entries_display(entries);
			put_cap("cr");
			lol = read_input(lol);
			if (lol[0] == 27 && !lol[1])
				exit(0);
			if (lol[0] == 27 && lol[2] == 68)
				cursor_on_prev(entries);
			if (lol[0] == 27 && lol[2] == 67)
				cursor_on_next(entries);
			put_cap("cd");
		}
	}
	return (0);
}
