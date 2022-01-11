# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/20 14:37:51 by rpohlen           #+#    #+#              #
#    Updated: 2022/01/11 17:11:51 by rpohlen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= fractol.c \
			  fractol_params.c \
			  fractol_params2.c \
			  fractol_params3.c \
			  fractol_colors.c \
			  fractol_colors_check.c \
			  fractol_colors_decode.c \
			  fractol_colors_decode2.c \
			  fractol_draw.c \
			  fractol_draw2.c \
			  fractol_list.c \
			  fractol_mlx.c \
			  fractol_printf.c \
			  fractol_keys.c \
			  fractol_keys2.c \
			  fractol_keys3.c \
			  fractol_init.c \
			  fractol_exit.c

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
