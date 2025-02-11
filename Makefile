# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/04 14:59:51 by ashahbaz          #+#    #+#              #
#    Updated: 2025/02/11 19:23:01 by ashahbaz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

RM = rm -f

CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address

SRCS =  main.c \
		error.c \
		validate_args.c \
		init_game.c \
		split.c \
		read_map.c \
		utils.c \
		utils_1.c \
		utils_2.c \
		utils_3.c \
		get_colour.c \
		map_integrity.c \
		init_window.c \
		validate_textures.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) cub3d.h Makefile
	cc $(CFLAGS) $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o:%.c
	cc $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
