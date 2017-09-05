/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handy_tools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 08:36:40 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/05 16:10:16 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int	sorted_array(char **entries_array)
{
	int		i;

	i = 0;
	while (entries_array[i + 1])
	{
		if (ft_strlen(entries_array[i]) < ft_strlen(entries_array[i + 1]))
			return (1);
		i++;
	}
	return (0);
}

static char	**sort_array(char **entries_array)
{
	int		i;
	char	*tmp;

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

char		**entries_array(t_all *usef)
{
	char	**dest;
	char	**start;
	t_list	*tmp;

	tmp = usef->elems;
	dest = (char **)malloc(sizeof(char *) * (count_entries(usef->elems) + 1));
	start = dest;
	*dest = ft_strdup(((t_elem *)(tmp->content))->value);
	tmp = tmp->next;
	while (tmp != usef->elems)
	{
		*dest = ft_strdup(((t_elem *)(tmp->content))->value);
		tmp = tmp->next;
		dest++;
	}
	*dest = NULL;
	return (sort_array(start));
}
