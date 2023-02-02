# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 21:00:39 by ebensalt          #+#    #+#              #
#    Updated: 2023/02/02 00:27:59 by ebensalt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D
C		=	src/get_next_line/get_next_line.c \
			src/get_next_line/get_next_line_utils.c \
			src/cub3d.c \
			src/ft_split.c \
			src/ft_split_new.c \
			src/ft_flex_split.c \
			parsing/parser.c \
			parsing/libft.c \
			parsing/view.c \
			parsing/color.c \
			parsing/texture.c \
			parsing/map.c \
			parsing/more_string.c
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