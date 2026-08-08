# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anematol <anematol@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/02 13:02:01 by anematol          #+#    #+#              #
#    Updated: 2026/08/08 19:44:40 by ssin             ###   ########.fr        #
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

#SRC_DIR = ./src

MLX_DIR = ./minilibx

MLX_REPO = https://github.com/42Paris/minilibx-linux.git

CFLAGS = -Wall -Wextra -Werror -g

CFLAGS += -I./includes -I./libft

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

CFILES =	main.c \
					minilibx.c \
					parser.c \
					hook_functions.c\

OFILES =	main.o \

INCLUDES	= cub.h

OBJ_DIR		= obj

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

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
		rm -rf $(OBJ_DIR)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
