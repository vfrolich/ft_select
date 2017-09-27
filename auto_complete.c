/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 11:42:28 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/27 14:01:59 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		select_new_entry(t_list *entries, t_list *to_select)
{
	t_list	*tmp;

	tmp = entries;
	while (((t_elem *)(tmp->content))->cursor != 1)
		tmp = tmp->next;
	((t_elem *)(tmp->content))->cursor = 0;
	((t_elem *)(to_select->content))->cursor = 1;
}

static int		dyna_search(t_list *entries, char *buffer, int c_read)
{
	t_list	*tmp;

	tmp = entries;
	if (!c_read)
		return (1);
	if (!ft_strncmp(((t_elem *)(tmp->content))->value, buffer, c_read))
	{
		select_new_entry(entries, tmp);
		return (0);
	}
	tmp = tmp->next;
	while (tmp != entries)
	{
		if (!ft_strncmp(((t_elem *)(tmp->content))->value, buffer, c_read))
		{
			select_new_entry(entries, tmp);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

static void		echo_search(int c)
{
	char	*tty_name;
	int		fd;

	if (c < 33 || c > 126)
		return ;
	fd = 0;
	if (!isatty(1))
	{
		tty_name = ttyname(0);
		fd = open(tty_name, O_WRONLY);
	}
	ft_putchar_fd(c, fd);
}

int				perfect_match(char *to_match, t_list *elems)
{
	t_list		*tmp;

	tmp = elems;
	if (!to_match)
		return (0);
	if (!ft_strcmp(to_match, ((t_elem *)(tmp->content))->value))
	{
		select_new_entry(elems, tmp);
		return (1);
	}
	tmp = tmp->next;
	while (tmp != elems)
	{
		if (!ft_strcmp(to_match, ((t_elem *)(tmp->content))->value))
		{
			select_new_entry(elems, tmp);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void			read_for_search(t_all *all_struct, char *oldbuff)
{
	char		*buffer;
	char		*to_search;
	char		*tmp;
	int			ret;

	if (*oldbuff != 9)
		return ;
	buffer = strgen(132);
	to_search = strgen(1);
	tmp = NULL;
	ret = 0;
	ft_putstr_fd("search: ", all_struct->fd);
	while (ft_isprint(*buffer) || !*buffer)
	{
		ret = ret + read(STDIN_FILENO, buffer, 1);
		tmp = ft_strdup(buffer);
		echo_search(*buffer);
		to_search = ft_strjoin_free(&to_search, &tmp);
		dyna_search(all_struct->elems, to_search, ret);
	}
	ft_strdel(&buffer);
	ft_strdel(&to_search);
}
