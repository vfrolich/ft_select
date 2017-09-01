/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   underline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 12:06:00 by vfrolich          #+#    #+#             */
/*   Updated: 2017/08/26 17:20:46 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	underline_word(char	*word)
{
	char 	*underline;
	int		(*display)(int);

	underline = get_capstring("us");
	display = ft_puts;
	tputs(underline, 1, display);
	ft_putstr(word);
	ft_bzero(underline, ft_strlen(underline));
	underline = get_capstring("ue");
	tputs(underline, 1, display);
}
