/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 20:32:20 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/13 22:03:19 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include <sys/stat.h>

static int			ft_get_type(struct stat *filestat)
{
	if (S_ISDIR(filestat->st_mode))
		return (1);
	if (S_ISSOCK(filestat->st_mode))
		return (2);
	if (S_ISREG(filestat->st_mode))
		return (3);
	if (S_ISBLK(filestat->st_mode))
		return (4);
	if (S_ISFIFO(filestat->st_mode))
		return (5);
	if (S_ISCHR(filestat->st_mode))
		return (6);
	if (S_ISLNK(filestat->st_mode))
		return (7);
	else
		return (0);
}

void				get_file_type(t_list *entries)
{
	t_list			*tmp;
	struct stat		filestat;

	tmp = entries;
	if (!lstat(((t_elem *)(tmp->content))->value, &filestat))
		((t_elem *)(tmp->content))->filetype = ft_get_type(&filestat);
	tmp = tmp->next;
	while (tmp != entries)
	{
		if (!lstat(((t_elem *)(tmp->content))->value, &filestat))
			((t_elem *)(tmp->content))->filetype = ft_get_type(&filestat);
		tmp = tmp->next;
	}
}

static void			put_color(char *color, char *target, int fd)
{
	ft_putchar_fd('\033', fd);
	ft_putstr_fd(color, fd);
	ft_putstr_fd(target, fd);
	ft_putchar_fd('\033', fd);
	ft_putstr_fd("[39m", fd);
}

void				print_color(t_list *elem, int fd)
{
	if (((t_elem *)(elem->content))->filetype == 1)
		put_color("[35m", ((t_elem *)(elem->content))->value, fd);
	else if (((t_elem *)(elem->content))->filetype == 3)
		put_color("[36m", ((t_elem *)(elem->content))->value, fd);
	else
		ft_putstr_fd(((t_elem *)(elem->content))->value, fd);
}
