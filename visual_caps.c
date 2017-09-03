/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_caps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 12:06:00 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/03 10:40:51 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_underliner(char *word)
{
	push_cap("us");
	ft_putstr(word);
	push_cap("ue");
}

void	inversed_video(char *word)
{
	push_cap("mr");
	ft_putstr(word);
	push_cap("me");
}

void	underlined_inversed(char *word)
{
	push_cap("us");
	push_cap("mr");
	ft_putstr(word);
	push_cap("ue");
	push_cap("me");
}
