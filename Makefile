# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/02 13:02:01 by anematol          #+#    #+#              #
#    Updated: 2026/09/03 19:52:38 by ssin             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
    MLX_FLAGS = -L$(MLX_DIR) -lmlx \
                -framework OpenGL \
                -framework AppKit
else
    MLX_FLAGS = -I$(MLX_DIR) -L$(MLX_DIR) \
                -lmlx -lXext -lX11 -lm -lbsd
endif

SRC_DIR = ./src

MLX_DIR = ./minilibx

MLX_REPO = https://github.com/42Paris/minilibx-linux.git

CFLAGS = -Wall -Wextra -Werror -g

CFLAGS += -I./includes -I./libft

SANITIZE_FLAGS := -fsanitize=address,undefined -fno-omit-frame-pointer

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

CFILES =	src/main.c \
			src/minilibx.c \
			src/hook_functions.c\
			src/draw.c\
			src/movement.c\
			src/parser/parser.c\
			src/parser/parser_colors.c\
			src/parser/parser_coordinates.c\
			src/parser/parser_helpers.c\
			src/parser/parser_map.c\

OFILES =	main.o \

INCLUDES	= include/cub.h

OBJ_DIR		= build

OBJ			= $(addprefix $(OBJ_DIR)/, $(notdir $(CFILES:.c=.o)))

all: $(MLX_DIR)/libmlx.a $(NAME)

$(MLX_DIR):
	git clone $(MLX_REPO) $(MLX_DIR)

$(MLX_DIR)/libmlx.a: $(MLX_DIR)
	$(MAKE) -C $(MLX_DIR) > /dev/null

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
		cc $(OBJ) $(CFLAGS) $(LIBFT) -o $(NAME) $(MLX_FLAGS)

vpath %.c $(SRC_DIR) $(SRC_DIR)/parser

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

sanitize:
	$(MAKE) CFLAGS="$(CFLAGS) $(SANITIZE_FLAGS)" re

clean:
		rm -rf $(OBJ_DIR)
		$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
		rm -f $(NAME)
		$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
