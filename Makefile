# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/20 14:37:51 by rpohlen           #+#    #+#              #
#    Updated: 2021/12/21 12:07:56 by rpohlen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= fractol.c \
			  fractol_utils.c \
			  fractol_utils_graph.c

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -O3 -Imlx

LIBS		= mlx/libmlx_Linux.a \
			  -lXext -lX11 -lm -lz

NAME		= fractol

OBJS		= $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			make -C mlx
			$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

all:		$(NAME)

clean:
			rm -rf $(OBJS)

fclean:		clean
			make clean -C mlx
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
