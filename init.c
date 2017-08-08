/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:20:21 by vfrolich          #+#    #+#             */
/*   Updated: 2017/08/08 17:21:38 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

char	*get_env_value(char *field, char **environ)
{
	char 	**tmp;
	size_t 	len;
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

void	init_checks(char **environ)
{
	char	*term_name;
	int		success;
	static	char	*term_buffer;

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
	if (!success)
	{
		ft_putendl_fd("current termtype is not referenced", 2);
		exit(1);
	}
	if (success < 0)
	{
		ft_putendl_fd("failed to load termcap database", 2);
		exit(1);
	}
}

t_list	*get_entries(char **argv)
{
	t_list	*head;
	t_list	*new;
	size_t	len;
	
	argv++;
	len = ft_strlen(*argv);
	head = ft_lstnew(*argv, len);
	argv++;
	while (*argv)
	{
		if (**argv)
		{
			len = ft_strlen(*argv);
			new = ft_lstnew(*argv, len);
			lst_add(new, &head);
		}
		argv++;
	}
	if (!head->next)
		head->next = head;
	else
		new->next = head;
	return (head);
}
