# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebensalt <ebensalt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 21:00:39 by ebensalt          #+#    #+#              #
#    Updated: 2023/02/20 06:27:15 by ebensalt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D
C		=	src/get_next_line/get_next_line.c \
			src/get_next_line/get_next_line_utils.c \
			src/cub3d.c \
			src/cub3d_utils_0.c \
			src/cub3d_utils_1.c \
			src/cub3d_utils_2.c \
			src/cub3d_utils_3.c \
			src/cub3d_utils_4.c \
			src/ft_split_new.c \
			src/ft_split.c \
			parsing/parser.c \
			parsing/more_parser.c \
			parsing/libft.c \
			parsing/color.c \
			parsing/more_color.c \
			parsing/texture.c \
			parsing/map.c \
			parsing/more_map.c \
			parsing/mmore_map.c \
			parsing/map_again.c \
			parsing/pixel.c \
			parsing/string.c \
			parsing/more_string.c
O		=	$(C:.c=.o)
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -Imlx
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