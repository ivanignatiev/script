##
## Makefile for minishell1 in /home/ignati_i//test_c/minishell1
## 
## Made by ivan ignatiev
## Login   <ignati_i@epitech.net>
## 
## Started on  Sat Nov  3 01:52:16 2012 ivan ignatiev
## Last update Sat Mar  2 20:00:15 2013 ivan ignatiev
##

SRCS	=	my_script.c \
		pts.c \
		script.c \
		shell.c

CFLAGS	+=	-Wall -Werror
CFLAGS	+=	-pedantic -Wextra

NAME	=	my_script

OBJS	=	$(SRCS:.c=.o)

CC	=	cc

RM	=	rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		re all fclean clean
