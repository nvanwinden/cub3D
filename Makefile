# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nvan-win <nvan-win@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/08/31 10:12:54 by nvan-win      #+#    #+#                  #
#    Updated: 2020/11/04 15:32:24 by nvan-win      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CFLAGS = -Wall -Wextra -Werror
HEADER_FILE = cub3d.h
INC_DIR = ./includes/
SRC_DIR = ./src/
PARSE_DIR = parser/
GAME_DIR = game/
LIBFT_DIR = ./libft/
LIBFT_LIB = libft.a
MLX_DIR = ./mlx/
MLX_LIB = libmlx.dylib
REG_SRC_FILES =		$(SRC_DIR)main.c \
					$(SRC_DIR)$(PARSE_DIR)check_map.c \
					$(SRC_DIR)$(PARSE_DIR)get_id_info.c \
					$(SRC_DIR)$(PARSE_DIR)get_map_utils.c \
					$(SRC_DIR)$(PARSE_DIR)get_map.c \
					$(SRC_DIR)$(PARSE_DIR)parse_scene.c \
					$(SRC_DIR)$(PARSE_DIR)parser_utils.c \
					$(SRC_DIR)$(GAME_DIR)start_game.c \
					$(SRC_DIR)$(GAME_DIR)init_game.c \
					$(SRC_DIR)$(GAME_DIR)set_texture.c \
					$(SRC_DIR)$(GAME_DIR)raycaster.c \
					$(SRC_DIR)$(GAME_DIR)raycaster_utils.c \
					$(SRC_DIR)$(GAME_DIR)sprites.c \
					$(SRC_DIR)$(GAME_DIR)sort_sprites.c \
					$(SRC_DIR)$(GAME_DIR)draw_sprite.c \
					$(SRC_DIR)$(GAME_DIR)move_player.c \
					$(SRC_DIR)$(GAME_DIR)rotate.c \
					$(SRC_DIR)$(GAME_DIR)save_bmp.c \

all: $(NAME)

$(NAME): $(REG_SRC_FILES) $(INC_DIR)$(HEADER_FILE)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(MLX_DIR)
	mv $(LIBFT_DIR)$(LIBFT_LIB) .
	mv $(MLX_DIR)$(MLX_LIB) .
	$(CC) $(CFLAGS) -O3 -L. -lft -lmlx $(REG_SRC_FILES) -o $(NAME)

clean:
	rm -f $(LIBFT_LIB) $(MLX_LIB)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
