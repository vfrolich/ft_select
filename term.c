/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 16:37:30 by vfrolich          #+#    #+#             */
/*   Updated: 2017/08/26 17:25:43 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	term_init()
{
	struct termios *term;

	term = get_term_struct();
	term->c_lflag &= !(ICANON);
	term->c_cc[VMIN] = 1;
	if (tcsetattr(0, TCSADRAIN, term) == -1)
	{
		ft_putendl_fd("ft_select: unable to set terminal, abort.", 2);
		exit(1);
	}
}
