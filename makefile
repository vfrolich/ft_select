CC				=	gcc
NAME			=	ft_select
FLAGS           =	-Wall -Wextra -Werror
LIB_PATH		=	libft
LIB				=   $(LIB_PATH)/libft.a
LIB_LINK		=	-Llibft -ltermcap -lft
SRC				=	main.c init.c line.c handy_tools.c display.c \
					entries_handle.c cursor.c visual_caps.c term.c signal.c \
					entries_handle_2.c color_files.c
HEADER			=	ft_select.h
OBJS			=	$(SRC:.c=.o)

all : $(NAME)

$(NAME) :
	@make -C $(LIB_PATH)
	@$(CC) $(FLAGS) -c $(SRC)
	@$(CC) $(OBJS)  $(LIB_LINK) -o $(NAME)

clean :
	@rm -f $(OBJS)
	@make -C $(LIB_PATH) clean

fclean : clean
	@rm -f $(NAME)
	@make -C $(LIB_PATH) fclean

re : fclean all