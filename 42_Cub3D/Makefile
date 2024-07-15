# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaqribei <jaqribei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/10 18:21:52 by jaqribei          #+#    #+#              #
#    Updated: 2024/07/15 00:13:11 by jaqribei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

#******************************************************************************#
#								COMPILATION									   #
#******************************************************************************#

CC = cc
FLAGS = -g3 -Wall -Wextra -Werror #-fsanitize=address

#******************************************************************************#
#									PATH									   #
#******************************************************************************#

LIBX		:= ./libs/MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm
INCLUDES	:= -I ./include -I ./libs/libft -I ./libs/MLX42/include/MLX42
SRC_DIR		:= src/
OBJ_DIR		:= obj/
MLX42		:= ./libs/MLX42/build/libmlx42.a

#******************************************************************************#
#									FILES									   #
#******************************************************************************#

src += main.c

src += $(addprefix parser/, cleanup.c \
							map_boundary_check.c \
							map_processing.c \
							map_utils.c \
							map_validation.c \
							parser.c \
							texture_processing.c \
							texture_utils.c \
							validate_input.c)

src += $(addprefix execution/, execution.c \
							player.c \
							player_key_manager.c \
							raycasting.c \
							raycasting_utils.c \
							rendering.c \
							rendering_utils.c \
							texture_management.c)

#******************************************************************************#
#									OBJECTS									   #
#******************************************************************************#

SRC_OBJ = $(addprefix $(OBJ_DIR)/, $(src:%.c=%.o))

$(OBJ_DIR)/%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@ 

#******************************************************************************#
#									TARGETS									   #
#******************************************************************************#

all: libft $(MLX42) $(NAME)

$(NAME): $(SRC_OBJ)
	@$(CC) $(FLAGS) $(SRC_OBJ) ./libs/libft/libft.a -o $(NAME) $(LIBX) $(INCLUDES)

libft:
	@make -C ./libs/libft

$(MLX42):
	@cmake ./libs/MLX42 -B ./libs/MLX42/build && make -C ./libs/MLX42/build -j4

clean:
	@rm -f $(SRC_OBJ) 
	@make clean -C ./libs/libft
	@make clean -C ./libs/MLX42/build

fclean: clean
	@rm -f $(NAME) $(MLX42) ./libs/libft/libft.a

re: fclean all 

norm:
	@norminette $(SRC) $(HEADER) ./libs/libft

gdb: re
	@gdb --tui --args ./$(NAME) assets/maps/baboon_maze.cub

valgrind: re
	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=mlx.sup ./$(NAME) assets/maps/baboon_maze.cub

run: all
	@./$(NAME) scenes/example.rt

.PHONY: all libft bonus clean fclean re valgrind norm gdb mlx
