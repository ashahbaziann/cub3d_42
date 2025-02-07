# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ashahbaz <ashahbaz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/04 14:59:51 by ashahbaz          #+#    #+#              #
#    Updated: 2025/02/07 16:27:33 by ashahbaz         ###   ########.fr        #
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
		are_textures_valid.c \
		are_walls_surrounding.c \
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
