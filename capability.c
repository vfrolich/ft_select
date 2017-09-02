/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capability.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 11:03:40 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/02 14:29:11 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	push_cap(char *const cap)
{
	char	*str;

	str = tgetstr(cap, NULL);
	if (str)
		write(STDIN_FILENO, str, ft_strlen(str));
	else
		write(STDERR_FILENO, "cap error\n", sizeof("cap error\n"));
}

char	*get_capstring(char *cap)
{
	char		*capability;
	static char	*buffer;

	buffer = strgen(1024);
	if (!(capability = tgetstr(cap, &buffer)))
	{
		ft_putstr_fd("ft_select: Failed to load \"", 2);
		ft_putstr_fd(cap, 2);
		ft_putendl_fd("\" capability string", 2);
		exit(1);
	}
	return (capability);
}

void	put_cap(char *cap)
{
	char	*cap_string;
	int		(*fptr)(int);

	cap_string = get_capstring(cap);
	fptr = ft_puts;
	tputs(cap_string, 1, fptr);
}
