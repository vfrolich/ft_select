/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:19:55 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/09 12:36:12 by vfrolich         ###   ########.fr       */
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
# include <sys/ioctl.h>

# define ENT ((t_elem *)(entries->content))

struct termios	g_term;

typedef struct		s_elem
{
	char			*value;
	int				selected;
	int				cursor;
}					t_elem;

typedef struct		s_printinfo
{
	int				nb_word;
	int				lines_needed;
	int				largest_word;
}					t_printinfo;

typedef struct		s_all
{
	t_list			*elems;
	char			**sorted_array;
	t_printinfo		*d_infos;
}					t_all;

/*
** initialisation
*/

void				term_init(void);
void				init_checks(void);
void				load_term_struct(void);
char				*get_term_infos(void);
t_all				*all_struct_init(t_list *entries);
t_list				*get_entries(char **argv);
int					setting_term(void);
char				**entries_array(t_all *usef);

/*
** visual capabilities
*/

void				ft_underliner(char *word);
void				underlined_inversed(char *word);
void				inversed_video(char	*word);

/*
** entries handle
*/

t_list				*remove_one(t_list *entries);
void				cursor_on_next(t_list *entry);
void				cursor_on_prev(t_list *entry);
void				select_cur(t_list *entries);
void				return_entries(t_list *entries);

/*
** signal handling
*/

void				all_signal_handler(void);
void				sig_handler(int sig);
void				term_rollback(void);

/*
** display
*/

size_t				get_term_size(char *field);
t_printinfo			*display_info(t_all *usef);
int					line_check(t_all *usef);
void				display_entries(t_all *usef);
void				push_cap(char *const cap);
void				screen_clear(t_printinfo *infos);

#endif
