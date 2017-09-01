/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 17:19:55 by vfrolich          #+#    #+#             */
/*   Updated: 2017/08/24 02:54:36 by vfrolich         ###   ########.fr       */
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

typedef struct 	s_entry
{
	char	*value;
	int		selected;
	int		cursor;
}				t_entry;

// retrieving info from term
char			*get_term_infos(void);
struct termios 	*get_term_struct(void);
char			*get_capstring(char *cap);

// line bufferisation handling

size_t	get_line_size(t_list *entries);
char	*line_init(t_list *entries);
int		line_check(size_t line_length);


// entries handle
void	flag_entry(t_list *entry, int on);
t_list	*entry_init_one(char *arg);
size_t 	count_entries(t_list *entries);
t_list	*get_entries(char **argv);
int		remove_one(t_list **entries);
void	cursor_on_next(t_list *entry);
void	cursor_on_prev(t_list *entry);


// terminal
char	*read_input();
void	term_init(void);
void	underline_word(char	*word);
void	move_up_cursor(void);
void	cursor_on_entries(void);

// display
void	put_cap(char *cap);
void	entries_display(t_list *entry);
int		ft_puts(int n);

// misc
char	*get_env_value(char *field, char **environ);
char 	*strgen(size_t lenght);
int		wordcut(char *str, size_t width);
void	init_checks(char **environ);

#endif