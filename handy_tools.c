/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handy_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:17:49 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/09 12:35:58 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static size_t	count_entries(t_list *entries)
{
	t_list		*tmp;
	size_t		count;

	tmp = entries;
	count = 1;
	tmp = tmp->next;
	while (tmp != entries)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

static int		sorted_array(char **entries_array)
{
	int			i;

	i = 0;
	while (entries_array[i + 1])
	{
		if (ft_strlen(entries_array[i]) < ft_strlen(entries_array[i + 1]))
			return (1);
		i++;
	}
	return (0);
}

static char		**sort_array(char **entries_array)
{
	int			i;
	char		*tmp;

	i = 0;
	while (entries_array[i + 1])
	{
		if (ft_strlen(entries_array[i]) < ft_strlen(entries_array[i + 1]))
		{
			tmp = entries_array[i];
			entries_array[i] = entries_array[i + 1];
			entries_array[i + 1] = tmp;
		}
		i++;
	}
	if (sorted_array(entries_array))
		sort_array(entries_array);
	return (entries_array);
}

char			**entries_array(t_all *usef)
{
	char		**dest;
	char		**start;
	t_list		*tmp;

	tmp = usef->elems;
	dest = (char **)malloc(sizeof(char *) * (count_entries(usef->elems) + 1));
	start = dest;
	*dest = ft_strdup(((t_elem *)(tmp->content))->value);
	tmp = tmp->next;
	dest++;
	while (tmp != usef->elems)
	{
		*dest = ft_strdup(((t_elem *)(tmp->content))->value);
		tmp = tmp->next;
		dest++;
	}
	*dest = NULL;
	return (sort_array(start));
}
