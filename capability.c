/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capability.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 11:03:40 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/03 11:15:59 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	push_cap(char *const cap)
{
	char	*str;

	str = tgetstr(cap, NULL);
	if (str)
		write(STDOUT_FILENO, str, ft_strlen(str));
	else
		write(STDERR_FILENO, "cap error\n", sizeof("cap error\n"));
}
