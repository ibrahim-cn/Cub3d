NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iminilibx-linux
MLX_FLAGS = -Lminilibx-linux -lmlx -lXext -lX11 -lm

SRC = main.c \
	cub_parsing/controller.c \
	cub_parsing/utils.c \
	cub_parsing/utils1.c \
	cub_parsing/map_check.c \
	cub_parsing/map_check_walls.c \
	cub_raycasting/raycasting.c \
	cub_raycasting/utils_render.c \
	cub_raycasting/map_utils.c \
	cub_raycasting/move.c \
	$(GNL_SRCS)

GNL_SRCS = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
GNL_OBJS = $(GNL_SRCS:.c=.o)

LIBFT = libft/libft.a

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@make -C libft
	@make -C minilibx-linux
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "✅ $(NAME) compiled"

clean:
	@make clean -C libft
	@rm -f $(OBJ) $(GNL_OBJS)
	@make -C minilibx-linux clean
	@echo "🧹 bye bye object files"

fclean:
	@make fclean -C libft
	@rm -rf $(OBJ)
	@rm -f $(NAME)
	@echo "🧼 fully cleaned up"

re: fclean all

.PHONY: all clean fclean re 