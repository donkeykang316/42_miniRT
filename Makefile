# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/21 16:03:38 by kaan              #+#    #+#              #
#    Updated: 2024/08/25 19:06:05 by kaan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_TARGET := all

NAME	=	minirt

CC		=	gcc
CFLAGS	=	-O2 -Wall -Werror -Wextra -Ilibmlx -g
MFLAGS  =	-L /usr/X11R6/lib -lXext -lX11 -lm

LIBS	=	./lib/libft/libft.a ./libmlx/libmlx.a

GNL  =  ./lib/get_next_line/gnl.a

SRCS	=	main.c\
			vector_init.c\
			data_init.c\
			interval.c\
			camera.c\
			camera_util.c\
			ray_color.c\
			sphere.c\
			material_util.c\
			vector_operation_1.c\
			vector_operation_2.c\
			vector_operation_3.c\
			vector_operation_4.c\
			vector_operation_5.c\
			random_generator.c\
			util.c\
			hooks.c\
			hooks_util.c\
			pixel.c\
			mlx_init.c\
			mlx_init_util.c\
			error.c\
			read_file.c\
			parser.c\
			parser_util_1.c\
			parser_util_2.c\
			parser_util_3.c\
			parser_util_4.c\
			print.c\
			plane.c\
			light.c\
			render.c\
			render_util_1.c\
			render_util_2.c\

OBJS	=	$(SRCS:.c=.o)

all:		$(NAME)

%.o: %.c minirt.h
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
			make -C ./lib/libft
			make -C ./lib/get_next_line
			make -C ./libmlx
			$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(GNL) -o $(NAME) $(MFLAGS)

test: all
	./$(NAME) ./scene/valid.rt

debug: re
	valgrind ./$(NAME)
			
clean:
			make clean -C ./lib/libft
			make clean -C ./lib/get_next_line
			make clean -C ./libmlx
			rm -rf $(OBJS)
			
fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY: all clean fclean re