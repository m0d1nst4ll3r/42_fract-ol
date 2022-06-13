# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpohlen <rpohlen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/25 17:00:48 by rpohlen           #+#    #+#              #
#    Updated: 2022/01/28 08:29:21 by rpohlen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CHAR		= ft_isalnum.c \
			  ft_isalpha.c \
			  ft_isascii.c \
			  ft_isdigit.c \
			  ft_ishex.c \
			  ft_isprint.c \
			  ft_isspace.c \
			  ft_tolower.c \
			  ft_toupper.c

LST			= ft_lstadd_back.c \
			  ft_lstadd_front.c \
			  ft_lstclear.c \
			  ft_lstdelone.c \
			  ft_lstiter.c \
			  ft_lstlast.c \
			  ft_lstmap.c \
			  ft_lstnew.c \
			  ft_lstsize.c

MEM			= ft_bzero.c \
			  ft_calloc.c \
			  ft_memalloc.c \
			  ft_memccpy.c \
			  ft_memchr.c \
			  ft_memcmp.c \
			  ft_memcpy.c \
			  ft_memdel.c \
			  ft_memdup.c \
			  ft_memmove.c \
			  ft_memset.c

PUT			= ft_putchar.c \
			  ft_putchar_fd.c \
			  ft_putendl.c \
			  ft_putendl_fd.c \
			  ft_putnbr.c \
			  ft_putnbr_base.c \
			  ft_putnbr_fd.c \
			  ft_putstr.c \
			  ft_putstr_fd.c

STR			= ft_split.c \
			  ft_strcat.c \
			  ft_strchr.c \
			  ft_strclr.c \
			  ft_strcmp.c \
			  ft_strcpy.c \
			  ft_strdel.c \
			  ft_strdup.c \
			  ft_strequ.c \
			  ft_striter.c \
			  ft_striteri.c \
			  ft_strjoin.c \
			  ft_strlcat.c \
			  ft_strlcpy.c \
			  ft_strlen.c \
			  ft_strmap.c \
			  ft_strmapi.c \
			  ft_strncat.c \
			  ft_strncmp.c \
			  ft_strncpy.c \
			  ft_strndup.c \
			  ft_strnequ.c \
			  ft_strnew.c \
			  ft_strnstr.c \
			  ft_strrchr.c \
			  ft_strstr.c \
			  ft_strtrim.c \
			  ft_strxcmp.c \
			  ft_substr.c \
			  ft_isint.c \
			  ft_isfloat.c

MATH		= ft_abs.c \
			  ft_fpow.c

GRAPH		= get_rgb.c \
			  get_r.c \
			  get_g.c \
			  get_b.c \
			  get_gradient.c \
			  get_gradient_palette.c

OTHER		= ft_atoi.c \
			  ft_atoi_base.c \
			  ft_atoi_strict.c \
			  ft_atof.c \
			  ft_convert_base.c \
			  ft_convert_base2.c \
			  ft_itoa.c \
			  ft_pendulum.c \
			  ft_realloc_byte.c

GNL			= get_next_line.c \
			  get_next_line_utils.c

PRINTF		= ft_printf.c \
			  ft_printf_args.c \
			  ft_printf_args2.c \
			  ft_printf_flags.c \
			  ft_printf_output.c \
			  ft_printf_utils.c \
			  ft_printf_utils_list.c \
			  ft_printf_utils_list2.c

SRC			= $(addprefix char/, $(CHAR)) \
			  $(addprefix lst/, $(LST)) \
			  $(addprefix mem/, $(MEM)) \
			  $(addprefix put/, $(PUT)) \
			  $(addprefix str/, $(STR)) \
			  $(addprefix math/, $(MATH)) \
			  $(addprefix graph/, $(GRAPH)) \
			  $(addprefix other/, $(OTHER)) \
			  $(addprefix gnl/, $(GNL)) \
			  $(addprefix printf/, $(PRINTF))

OBJS		= ${SRC:.c=.o}

NAME		= libft.a

CC			= cc
LIB			= ar rcs
RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror -Wno-unused-result -O3 -I include/

${NAME}:	${OBJS}
			${LIB} $@ $?

all:		${NAME}

clean:
			${RM} ${OBJS} ${OBJSB}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
