NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iminilibx-linux

MLX_PATH = ./minilibx-linux
MLX_REPO = https://github.com/42Paris/minilibx-linux.git
MLX = $(MLX_PATH)/libmlx.a
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a
LIBFT_FLAGS = -L$(LIBFT_PATH) -lft

# ---------------------- SRCS -------------------------

GNL_SRCS = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

SRC = main.c \
	main_utils.c \
	cub_parsing/check_component.c \
	cub_parsing/controls.c \
	cub_parsing/copy_map.c \
	cub_parsing/utils.c \
	cub_parsing/utils1.c \
	cub_parsing/map_check.c \
	cub_parsing/map_check2.c \
	cub_parsing/map_check_walls.c \
	cub_parsing/map_check_walls_v2.c \
	cub_parsing/parsing_color.c \
	cub_parsing/parsing_color2.c \
	cub_raycasting/raycasting.c \
	cub_raycasting/raycast_dda.c \
	cub_raycasting/raycast_dda_v2.c \
	cub_raycasting/raycast_draw.c \
	cub_raycasting/raycast_texture.c \
	cub_raycasting/utils_render.c \
	cub_raycasting/utils_render_v2.c \
	cub_raycasting/map_utils.c \
	cub_raycasting/move.c \
	cub_raycasting/rotate.c \
	cub_raycasting/initialize.c \
	cub_raycasting/hooks.c \
	$(GNL_SRCS)

OBJ = $(SRC:.c=.o)

# -----------------------------------------------------

all: clone_mlx $(NAME)

clone_mlx:
	@if [ ! -d "$(MLX_PATH)" ]; then \
		echo "📥 Cloning MLX repository..."; \
		git clone $(MLX_REPO) $(MLX_PATH); \
	fi

$(MLX): clone_mlx
	@make -C $(MLX_PATH) --no-print-directory
	@echo "🔧 MLX Ready!"

$(LIBFT):
	@make -C $(LIBFT_PATH) --no-print-directory
	@echo "🔧 LIBFT Ready!"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $<"

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)
	@echo "🎉 $(NAME) Ready!"

clean:
	@make -C $(LIBFT_PATH) clean --no-print-directory || true
	@make -C $(MLX_PATH) clean --no-print-directory || true
	@rm -f $(OBJ)
	@echo "🧹 Object files removed"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean --no-print-directory || true
	@echo "🧼 Full clean done"

re: fclean all

.PHONY: all clean fclean re clone_mlx
