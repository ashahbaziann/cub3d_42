# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/04 14:59:51 by ashahbaz          #+#    #+#              #
#    Updated: 2025/03/31 16:23:59 by ashahbaz         ###   ########.fr        #
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
		update.c \
		raycast.c \
		events.c \
		load_textures.c \
		draw.c \

GNL =	get_next_line.c \
		get_next_line_utils.c \
		
SRCS_DIR = ./srcs/
GNL_DIR = ./gnl/
SRCS := $(addprefix $(SRCS_DIR), $(SRCS))
GNL := $(addprefix $(GNL_DIR), $(GNL))
SRCS := $(SRCS) $(GNL)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) -Lmlx -lmlx -lX11 -lXext -lm -o $(NAME)

%.o:%.c
	cc $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
