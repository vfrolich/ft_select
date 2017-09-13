/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_caps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 12:06:00 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/13 21:59:38 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_underliner(t_list *entry, int fd)
{
	push_cap("us");
	print_color(entry, fd);
	push_cap("ue");
}

void	inversed_video(t_list *entry, int fd)
{
	push_cap("mr");
	print_color(entry, fd);
	push_cap("me");
}

void	underlined_inversed(t_list *entry, int fd)
{
	push_cap("us");
	push_cap("mr");
	print_color(entry, fd);
	push_cap("ue");
	push_cap("me");
}
