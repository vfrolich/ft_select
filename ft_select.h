/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:19:55 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/08 15:13:27 by vfrolich         ###   ########.fr       */
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
** retrieving info from term
*/

size_t				get_term_size(char *field);
char				*get_term_infos(void);
void				load_term_struct(void);
t_all				*all_struct_init(t_list *entries);

/*
** line bufferisation handling
*/

size_t				get_line_size(t_list *entries);
char				*line_init(t_list *entries);
int					line_check(t_all *usef);

/*
** entries handle
*/

t_list				*entry_init_one(char *arg);
size_t				count_entries(t_list *entries);
t_list				*get_entries(char **argv);
t_list				*remove_one(t_list *entries);
void				cursor_on_next(t_list *entry);
void				cursor_on_prev(t_list *entry);
void				select_cur(t_list *entries);
int					another_one_selected(t_list *entries);
void				return_entries(t_list *entries);
void				entry_return_one(t_list *entries);

/*
** signal handling
*/

void				all_signal_handler(void);
void				sig_handler(int sig);

/*
** terminal
*/

int					setting_term(void);
void				term_rollback(void);
char				*read_input();
void				term_init(void);
void				ft_underliner(char *word);
void				underlined_inversed(char *word);
void				inversed_video(char	*word);

/*
** display
*/

t_printinfo			*display_info(t_all *usef);
void				display_entries(t_all *usef);
int					ft_puts(int n);
void				push_cap(char *const cap);

/*
** misc
*/

char				*get_env_value(char *field, char **environ);
char				*strgen(size_t lenght);
int					wordcut(char *str, size_t width);
void				init_checks(void);
char				**entries_array(t_all *usef);

#endif
