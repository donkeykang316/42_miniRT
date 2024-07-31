# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/21 16:03:38 by kaan              #+#    #+#              #
#    Updated: 2024/07/31 15:23:21 by kaan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minirt

CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -Imlx -g
MFLAGS  =	-lm

LIBS	=	./lib/libft/libft.a

GNL  =  ./lib/get_next_line/gnl.a

SRCS	=	main.c\
			vector_init.c\
			data_init.c\
			interval.c\
			camera.c\
			camera_util.c\
			objects.c\
			material.c\
			material_util.c\
			vector_operation_1.c\
			vector_operation_2.c\
			vector_operation_3.c\
			vector_operation_4.c\
			vector_operation_5.c\
			random_generator.c\
			util.c\
			tester.c\

OBJS	=	$(SRCS:.c=.o)

all:		$(NAME)

$(NAME): $(OBJS)
			make -C ./lib/libft
			make -C ./lib/get_next_line
			$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(GNL) -o $(NAME) $(MFLAGS)
			./$(NAME) > img.ppm
			
clean:
			make clean -C ./lib/libft
			make clean -C ./lib/get_next_line
			rm -rf $(OBJS)
			
fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY: all clean fclean re