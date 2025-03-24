# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/04 14:59:51 by ashahbaz          #+#    #+#              #
#    Updated: 2025/03/11 14:58:31 by ashahbaz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

RM = rm -f

CFLAGS = -Wall -Werror -Wextra -g3 -I.  -Imlx #-g3 -fsanitize=address

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
		map_parsing.c \
		init_window.c \
		validate_textures.c \
		gnl/get_next_line.c \
		gnl/get_next_line_utils.c \
		handle_movement.c \
		raycast.c \
		events.c \


OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)  Makefile cub3d.h
	cc $(CFLAGS) $(OBJS) -Lmlx -lmlx -lX11 -lXext -lm -o $(NAME)

%.o:%.c Makefile $(HEADERS)
	cc $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
