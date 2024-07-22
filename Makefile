# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaan <kaan@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/21 16:03:38 by kaan              #+#    #+#              #
#    Updated: 2024/07/22 14:52:42 by kaan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minirt

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -Imlx -g 

LIBS	=	./lib/libft/libft.a

GNL  =  ./lib/get_next_line/gnl.a

SRCS	=	main.c\
			vector_init.c\
			data_init.c\
			secene_render.c\
			vector_operation_1.c\
			vector_operation_2.c\
			vector_operation_3.c\
			vector_operation_4.c\

OBJS	=	$(SRCS:.c=.o)

all:		$(NAME)

$(NAME): $(OBJS)
			make -C ./lib/libft
			make -C ./lib/get_next_line
			$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(GNL) -o $(NAME)
			
clean:
			make clean -C ./lib/libft
			make clean -C ./lib/get_next_line
			rm -rf $(OBJS)
			
fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY: all clean fclean re