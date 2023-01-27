# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aniouar <aniouar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 21:00:39 by ebensalt          #+#    #+#              #
#    Updated: 2023/01/27 10:40:16 by aniouar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D
C		=	src/get_next_line/get_next_line.c \
			src/get_next_line/get_next_line_utils.c \
			src/cub3d.c \
			src/ft_split.c \
			parsing/parser.c parsing/libft.c
O		=	$(C:.c=.o)
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -Imlx -D BUFFER_SIZE=1 
MLX		=	-lmlx -framework OpenGL -framework AppKit
all		:	$(NAME)
$(NAME)	:	$(O)
	$(CC) $(CFLAGS) $(O) $(MLX) -o $(NAME)
	# clear
clean	:
	rm -rf */*.o */*/*.o
	# clear
fclean	:	clean
	rm -rf $(NAME)
	# clear
re		:	fclean	all