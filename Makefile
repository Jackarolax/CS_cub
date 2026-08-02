# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/02 13:02:01 by anematol          #+#    #+#              #
#    Updated: 2026/08/02 13:26:34 by anematol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SRC_DIR = ./src

MLX_DIR = ./minilibx

MLX_REPO = https://github.com/42Paris/minilibx-linux.git

CFLAGS = -Wall -Wextra -Werror

MLX_FLAGS = -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

CFILES =	main.c\


OFILES =	main.o\

INCLUDES = cub.h

NAME = cub3D

all: $(MLX_DIR)/libmlx.a $(NAME)

$(MLX_DIR):
	git clone $(MLX_REPO) $(MLX_DIR)

$(MLX_DIR)/libmlx.a: $(MLX_DIR)
	$(MAKE) -C $(MLX_DIR) > /dev/null

$(OFILES): $(CFILES) $(INCLUDES)
		cc $(CFLAGS) -c $(CFILES)

$(NAME): $(OFILES)
		cc $(CFLAGS)  $(OFILES) -o $(NAME) $(MLX_FLAGS)

clean:
		rm -f $(OFILES)

fclean: clean
		rm -f $(NAME)

re: fclean all
