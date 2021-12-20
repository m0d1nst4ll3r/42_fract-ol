# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/20 14:37:51 by rpohlen           #+#    #+#              #
#    Updated: 2021/12/20 18:16:47 by rpohlen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= fractol.c

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

LIB			= mlx/libmlx_Linux.a

NAME		= fractol

OBJS		= $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(LIB) -lXext -lX11 -lm -lz -o $(NAME)

all:		$(NAME)

clean:
			rm -rf $(OBJS)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
