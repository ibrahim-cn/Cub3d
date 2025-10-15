NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c utils.c map_check.c

LIBFT = libft/libft.a

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@make -C libft -silent
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) 
	@echo "✅ $(NAME) compiled"

clean:
	@make clean -C libft -silent
	@rm -f $(OBJ)
	@echo "🧹 bye bye object files"

fclean:
	@make fclean -C libft -silent
	@rm -rf $(OBJ)
	@rm -f $(NAME)
	@echo "🧼 fully cleaned up"

re: fclean all

.PHONY: all clean fclean re 