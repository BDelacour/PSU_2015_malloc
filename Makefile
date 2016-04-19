##
## Makefile for C in /home/delaco_c/rendu/PSU_2015_malloc
## 
## Made by Delacour Benjamin
## Login   <delaco_c@epitech.net>
## 
## Started on  Wed Jan 27 15:29:15 2016 Delacour Benjamin
## Last update Mon Feb  8 02:51:25 2016 Benjamin Delacour
##

NAME	=	libmy_malloc.so

CC	=	gcc

RM	=	rm -f

CFLAGS	+=	-Wextra -Wall -Werror -fpic

SRCS	=	my_malloc.c		\
		my_realloc.c		\
		my_calloc.c		\
		my_free.c		\
		show_alloc_mem.c	\
		my_malloc_tool.c	\
		my_mutex.c

OBJS	=	$(SRCS:.c=.o)

all	:	$(NAME)

$(NAME)	:	$(OBJS)
		$(CC) -shared -o $(NAME) $(OBJS)

clean	:
		$(RM) $(OBJS)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re
