/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:19:55 by vfrolich          #+#    #+#             */
/*   Updated: 2017/08/08 17:21:55 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H
# include "libft/libft.h"
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
# include <curses.h>
# include <term.h>

// retrieving info from term
char	*get_term_infos(void);
char	*get_env_value(char *field, char **environ);
// line bufferisation handling
size_t	get_line_size(t_list *entries);
char	*line_init(t_list *entries);
// misc
char 	*strgen(size_t lenght);
void	init_checks(char **environ);
t_list	*get_entries(char **argv);

#endif