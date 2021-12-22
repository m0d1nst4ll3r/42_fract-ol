# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/20 14:37:51 by rpohlen           #+#    #+#              #
#    Updated: 2021/12/22 19:13:25 by rpohlen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= fractol.c \
			  fractol_colors_check.c \
			  fractol_colors_decode.c \
			  fractol_colors_decode2.c \
			  fractol_utils.c \
			  fractol_utils_color.c \
			  fractol_utils_color2.c \
			  fractol_utils_list.c \

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Imlx -Ilibft/includes

LIBS		= mlx/libmlx_Linux.a \
			  libft/libft.a \
			  -lXext -lX11 -lm -lz

NAME		= fractol

OBJS		= $(SRCS:.c=.o)

$(NAME):	$(OBJS)
			make -C mlx
			make -C libft
			$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

all:		$(NAME)

clean:
			make clean -C libft
			rm -rf $(OBJS)

fclean:		clean
			make fclean -C libft
			make clean -C mlx
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
