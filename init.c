/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:20:21 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/03 11:14:08 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_list	*entry_init_one(char *arg)
{
	t_elem	*entry;
	t_list	*dest;

	if (!(entry = (t_elem *)malloc(sizeof(t_elem))))
	{
		ft_putendl_fd("ft_select: malloc error", 2);
		exit(1);
	}
	entry->value = strgen(ft_strlen(arg));
	entry->value = ft_strcpy(entry->value, arg);
	entry->cursor = 0;
	entry->selected = 0;
	if (!(dest = ft_lstnew(entry, sizeof(entry))))
	{
		ft_putendl_fd("ft_select: malloc error", 2);
		exit(1);
	}
	free(entry);
	return (dest);
}

char	*get_env_value(char *field, char **environ)
{
	char	**tmp;
	size_t	len;
	char	*value;

	len = ft_strlen(field);
	tmp = environ;
	while (*environ)
	{
		if (!ft_strncmp(field, *environ, len))
		{
			value = ft_strsub(*environ, len, ft_strlen(*environ) - len);
			environ = tmp;
			return (value);
		}
		environ++;
	}
	environ = tmp;
	return (NULL);
}

void	init_checks(void)
{
	char			*term_name;
	int				success;
	static char		*term_buffer;
	extern char		**environ;

	if (!(term_name = get_env_value("TERM=", environ)))
	{
		ft_putendl_fd("failed to find term name from environ", 2);
		exit(1);
	}
	if (!(term_buffer = ft_strnew(2048)))
	{
		ft_putendl_fd("malloc of term_buffer failed", 2);
		exit(1);
	}
	success = tgetent(term_buffer, term_name);
	if (success <= 0)
	{
		!success ? ft_putendl_fd("current termtype is not referenced", 2)
		: ft_putendl_fd("failed to load termcap database", 2);
		exit(1);
	}
	ft_strdel(&term_name);
}
