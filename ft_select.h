/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:19:55 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/02 16:01:03 by vfrolich         ###   ########.fr       */
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

# define ARG entry->content

typedef struct		s_elem
{
	char			*value;
	int				selected;
	int				cursor;
}					t_elem;

typedef struct		s_all
{
	t_list			*elems;
	struct termios	term;
	int				co;
	int				li;
}					t_all;

/*
** retrieving info from term
*/

char				*get_term_infos(void);
struct termios		get_term_struct(void);
char				*get_capstring(char *cap);

/*
** line bufferisation handling
*/

size_t				get_line_size(t_list *entries);
char				*line_init(t_list *entries);
int					line_check(size_t line_length);

/*
** entries handle
*/

t_list				*entry_init_one(char *arg);
size_t				count_entries(t_list *entries);
t_list				*get_entries(char **argv);
int					remove_one(t_list **entries);
void				cursor_on_next(t_list *entry);
void				cursor_on_prev(t_list *entry);
void				select_cur(t_list *entries);

/*
** signal handling
*/

void				sig_handler(int sig);

/*
** terminal
*/

int					setting_term(void);
void				term_rollback(struct termios term);
char				*read_input();
void				term_init(void);
void				ft_underliner(char *word);
void				underlined_inversed(char *word);
void				inversed_video(char	*word);

/*
** display
*/

void				put_cap(char *cap);
void				display_entries(t_list *entry);
int					ft_puts(int n);
void				push_cap(char *const cap);

/*
** misc
*/

char				*get_env_value(char *field, char **environ);
char				*strgen(size_t lenght);
int					wordcut(char *str, size_t width);
void				init_checks(void);

#endif
