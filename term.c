/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrolich <vfrolich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 16:37:30 by vfrolich          #+#    #+#             */
/*   Updated: 2017/09/09 12:27:15 by vfrolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int					setting_term(void)
{
	struct termios	term;

	if (tgetent(NULL, getenv("TERM")) == -1)
	{
		write(STDERR_FILENO, "tgetent\n", sizeof("tgetent\n"));
		exit(1);
	}
	if (tcgetattr(0, &term) == -1)
	{
		ft_putendl_fd("ft_select: failed to load termios struct", 2);
		return (1);
	}
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	push_cap("ti");
	push_cap("ho");
	push_cap("vi");
	if (tcsetattr(0, TCSANOW, &term) == -1)
		ft_putendl_fd("ft_select: failed to apply changes on term", 2);
	return (0);
}

void				load_term_struct(void)
{
	ft_bzero(&g_term, sizeof(struct termios));
	if (tcgetattr(0, &g_term) == -1)
	{
		ft_putendl_fd("ft_select: failed to load termios struct, abort", 2);
		exit(1);
	}
	if (tcgetattr(0, &g_term) == -1)
	{
		ft_putendl_fd("ft_select: failed to load termios struct, abort", 2);
		exit(1);
	}
}

static char			*get_env_value(char *field, char **environ)
{
	char			**tmp;
	size_t			len;
	char			*value;

	len = ft_strlen(field);
	tmp = environ;
	while (*environ)
	{
		if (!ft_strncmp(field, *environ, len))
		{
			value = ft_strsub(*environ, len, ft_strlen(*environ) - len);
			environ = tmp;
			return (value);
		}
		environ++;
	}
	environ = tmp;
	return (NULL);
}

void				init_checks(void)
{
	char			*term_name;
	int				success;
	static char		*term_buffer;
	extern char		**environ;

	if (!(term_name = get_env_value("TERM=", environ)))
	{
		ft_putendl_fd("failed to find term name from environ", 2);
		exit(1);
	}
	if (!(term_buffer = ft_strnew(2048)))
	{
		ft_putendl_fd("malloc of term_buffer failed", 2);
		exit(1);
	}
	success = tgetent(term_buffer, term_name);
	if (success <= 0)
	{
		!success ? ft_putendl_fd("current termtype is not referenced", 2)
		: ft_putendl_fd("failed to load termcap database", 2);
		exit(1);
	}
	ft_strdel(&term_name);
}
