/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:21:04 by vfrolich          #+#    #+#             */
/*   Updated: 2017/08/08 17:21:48 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int main(int argc, char **argv, char **environ)
{
	t_list 	*entries;
	char	*line;

	if (argc > 1)
	{
		entries = get_entries(argv);
		init_checks(environ);
		while (42)
		{
			ft_putstr(line_init(entries));
			get_next_line(0, &line);
		}
	}
	return (0);
}	